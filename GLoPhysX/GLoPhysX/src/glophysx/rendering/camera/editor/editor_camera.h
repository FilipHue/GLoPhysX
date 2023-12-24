#pragma once

#include "glophysx/rendering/camera/simple_camera.h"
#include "glophysx/core/time/time.h"
#include "glophysx/core/events/event.h"
#include "glophysx/core/events/mouse_events.h"

namespace GLOPHYSX {

	namespace RENDERING {

		class EditorCamera : public SimpleCamera
		{
		public:
			EditorCamera() = default;
			EditorCamera(float fov, float aspect_ration, float near_z, float far_z);
			~EditorCamera() = default;

			void OnUpdate(DeltaTime dt);
			void OnEvent(Event& e);

			void SetViewportSize(float width, float height) { m_viewport_size.x = width, m_viewport_size.y = height; UpdateProjection(); }

			glm::mat4 GetViewMatrix() const { return m_view_matrix; }
			glm::mat4 GetVPMatrix() const { return m_projection_matrix * m_view_matrix; }

			float GetYaw() const { return m_yaw; }
			float GetPitch() const { return m_pitch; }
			float GetRoll() const { return m_roll; }

			glm::vec3 GetUpDirection() const;
			glm::vec3 GetRightDirection() const;
			glm::vec3 GetForwardDirection() const;
			const glm::vec3& GetPosition() const { return m_position; }
			glm::quat GetOrientation() const;

		private:
			void UpdateProjection();
			void UpdateView();

			bool OnMouseScroll(MouseScrollEvent& e);

			void MousePan(const glm::vec2& delta);
			void MouseRotate(const glm::vec2& delta);
			void MouseZoom(float delta);

			glm::vec3 CalculatePosition() const;

			std::pair<float, float> PanSpeed() const;
			float RotationSpeed() const;
			float ZoomSpeed() const;

		private:
			glm::mat4 m_view_matrix = glm::mat4(1.0f);
			glm::mat4 m_vp_matrix = glm::mat4(1.0f);

			glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_focal_point = { 0.0f, 0.0f, 0.0f };

			glm::vec3 m_global_forward = glm::vec3(0, 0, 1);
			glm::vec3 m_global_up = glm::vec3(0, 1, 0);
			glm::vec3 m_global_right = glm::vec3(1, 0, 1);

			glm::vec3 m_forward = m_global_forward;
			glm::vec3 m_up = m_global_up;
			glm::vec3 m_right = m_global_right;

			float m_fov = 45.0f, m_aspect_ratio = 1.78f, m_near = 0.1f, m_far = 1000.0f;
			float m_yaw = 0.0f, m_pitch = 0.0f, m_roll = 0.0f;
			float m_distance = 10.0f;

			glm::vec2 m_mouse_position = glm::vec2(0.0f, 0.0f);

			glm::vec2 m_viewport_size = glm::vec2{ 1600.0f, 900.0f };
		};
	}
}
