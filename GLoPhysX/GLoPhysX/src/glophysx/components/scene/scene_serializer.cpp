#include "gxpch.h"
#include "scene_serializer.h"

#include "glophysx/ecs/entity.h"
#include "glophysx/ecs/components.h"

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);

			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();

			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);

			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();

			return true;
		}
	};
}

namespace GLOPHYSX {

	namespace COMPONENTS {

		static YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
		{
			out << YAML::Flow;
			out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;

			return out;
		}

		static YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
		{
			out << YAML::Flow;
			out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;

			return out;
		}

		SceneSerializer::SceneSerializer(const Shared<Scene>& scene)
		{
			m_scene = scene;
		}

		static void SerializeEntity(YAML::Emitter& out, Entity entity)
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Entity" << YAML::Value << "1234";

			if (entity.HasComponent<TagComponent>())
			{
				out << YAML::Key << "TagComponent";
				out << YAML::BeginMap;

				auto& tag = entity.GetComponent<TagComponent>().m_tag;

				out << YAML::Key << "Tag" << YAML::Value << tag;

				out << YAML::EndMap;
			}

			if (entity.HasComponent<TransformComponent>())
			{
				out << YAML::Key << "TransformComponent";
				out << YAML::BeginMap;

				auto& tc = entity.GetComponent<TransformComponent>();

				out << YAML::Key << "Translation" << YAML::Value << tc.m_translation;
				out << YAML::Key << "Rotation" << YAML::Value << tc.m_rotation;
				out << YAML::Key << "Scale" << YAML::Value << tc.m_scale;

				out << YAML::EndMap;
			}

			if (entity.HasComponent<CameraComponent>())
			{
				out << YAML::Key << "CameraComponent";
				out << YAML::BeginMap;

				auto& cc = entity.GetComponent<CameraComponent>();

				out << YAML::Key << "Camera" << YAML::Value;
				out << YAML::BeginMap;
				out << YAML::Key << "ProjectionType" << YAML::Value << (int)cc.m_camera.GetProjectionType();

				out << YAML::Key << "PerspectiveFOV" << YAML::Value << cc.m_camera.GetPerspectiveProjectionFov();
				out << YAML::Key << "PerspectiveNear" << YAML::Value << cc.m_camera.GetPerspectiveNearZ();
				out << YAML::Key << "PerspectiveFar" << YAML::Value << cc.m_camera.GetPerspectiveFarZ();

				out << YAML::Key << "OrthographicSize" << YAML::Value << cc.m_camera.GetOrthographicProjectionSize();
				out << YAML::Key << "OrthographicNear" << YAML::Value << cc.m_camera.GetOrthographicNearZ();
				out << YAML::Key << "OrthographicFar" << YAML::Value << cc.m_camera.GetOrthographicFarZ();
				out << YAML::EndMap;

				out << YAML::Key << "Primary" << YAML::Value << cc.is_primary;
				out << YAML::Key << "FixedAspectRatio" << YAML::Value << cc.fixed_aspect_ratio;

				out << YAML::EndMap;
			}

			if (entity.HasComponent<SpriteComponent>())
			{
				out << YAML::Key << "SpriteComponent";
				out << YAML::BeginMap;

				auto& sc = entity.GetComponent<SpriteComponent>();

				out << YAML::Key << "Color" << YAML::Value << sc.m_color;

				out << YAML::EndMap;
			}

			out << YAML::EndMap;
		}

		void SceneSerializer::Serialize(const std::string& file_path)
		{
			YAML::Emitter out;

			out << YAML::BeginMap;
			out << YAML::Key << "Scene" << YAML::Value << "Untitled";
			out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

			auto entities = m_scene->m_registry.storage<entt::entity>().each();
			for (const auto& [entity_id] : entities)
			{
				Entity entity = { entity_id, m_scene.get() };
				if (!entity)
				{
					return;
				}

				SerializeEntity(out, entity);
			}

			out << YAML::EndSeq;
			out << YAML::EndMap;

			std::ofstream fout(file_path);
			fout << out.c_str();
		}

		void SceneSerializer::SerializeRuntime(const std::string& file_path)
		{
			return;
		}

		bool SceneSerializer::Deserialize(const std::string& file_path)
		{
			std::ifstream stream(file_path);
			std::stringstream str_stream;

			str_stream << stream.rdbuf();

			YAML::Node data = YAML::Load(str_stream.str());
			if (!data["Scene"]) {
				return false;
			}

			std::string scene_name = data["Scene"].as<std::string>();

			auto entities = data["Entities"];
			if (entities)
			{
				for (auto entity : entities)
				{
					uint64_t uuid = entity["Entity"].as<uint64_t>();

					std::string name;
					auto tag_component = entity["TagComponent"];
					if (tag_component)
					{
						name = tag_component["Tag"].as<std::string>();
					}

					Entity deserialized_entity = m_scene->CreateEntity(name);

					auto transform_component = entity["TransformComponent"];
					if (transform_component)
					{
						auto& tc = deserialized_entity.GetComponent<TransformComponent>();

						tc.m_translation = transform_component["Translation"].as<glm::vec3>();
						tc.m_rotation = transform_component["Rotation"].as<glm::vec3>();
						tc.m_scale = transform_component["Scale"].as<glm::vec3>();
					}

					auto camera_component = entity["CameraComponent"];
					if (camera_component)
					{
						auto& cc = deserialized_entity.AddComponent<CameraComponent>();

						auto& cameraProps = camera_component["Camera"];
						cc.m_camera.SetProjectionType((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());

						cc.m_camera.SetPerspectiveProjectionFov(cameraProps["PerspectiveFOV"].as<float>());
						cc.m_camera.SetPerspectiveNearZ(cameraProps["PerspectiveNear"].as<float>());
						cc.m_camera.SetPerspectiveFarZ(cameraProps["PerspectiveFar"].as<float>());

						cc.m_camera.SetOrthographicProjectionSize(cameraProps["OrthographicSize"].as<float>());
						cc.m_camera.SetOrthographicNearZ(cameraProps["OrthographicNear"].as<float>());
						cc.m_camera.SetOrthographicFarZ(cameraProps["OrthographicFar"].as<float>());

						cc.is_primary = camera_component["Primary"].as<bool>();
						cc.fixed_aspect_ratio = camera_component["FixedAspectRatio"].as<bool>();
					}

					auto sprite_component = entity["SpriteComponent"];
					if (sprite_component)
					{
						auto& src = deserialized_entity.AddComponent<SpriteComponent>();
						src.m_color = sprite_component["Color"].as<glm::vec4>();
					}
				}
			}

			return true;
		}

		bool SceneSerializer::DeserializeRuntime(const std::string& file_path)
		{
			return false;
		}
	}
}