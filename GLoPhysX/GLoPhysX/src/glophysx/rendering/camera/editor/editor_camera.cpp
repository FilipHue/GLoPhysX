#include "gxpch.h"
#include "editor_camera.h"

#include "glophysx/core/input/input.h"
#include "glophysx/core/input/keycodes.h"
#include "glophysx/core/input/mouse_codes.h"

#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/quaternion.hpp"

namespace GLOPHYSX {

	namespace RENDERING {

		EditorCamera::EditorCamera(float fov, float aspect_ration, float near_z, float far_z)
		{
			m_fov = fov;
			m_aspect_ratio = aspect_ration;
			m_near = near_z;
			m_far = far_z;

			UpdateView();
		}

		void EditorCamera::OnUpdate(DeltaTime dt)
		{
			if (Input::IsKeyPressed(GLOP_KEY_LEFT_ALT))
			{
				const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
				glm::vec2 delta = (mouse - m_mouse_position) * 0.003f;
				m_mouse_position = mouse;

				if (Input::IsMouseButtonPressed(GLOP_MOUSE_BUTTON_2))
					MousePan(delta);
				else if (Input::IsMouseButtonPressed(GLOP_MOUSE_BUTTON_1))
					MouseRotate(delta);
				else if (Input::IsMouseButtonPressed(GLOP_MOUSE_BUTTON_3))
					MouseZoom(delta.y);
			}

			UpdateView();
		}

		void EditorCamera::OnEvent(Event& e)
		{
			EventDispatcher::Dispatch<MouseScrollEvent>(e, std::bind(&EditorCamera::OnMouseScroll, this, std::placeholders::_1));
		}

		glm::vec3 EditorCamera::GetUpDirection() const
		{
			return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
		}

		glm::vec3 EditorCamera::GetRightDirection() const
		{
			return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		glm::vec3 EditorCamera::GetForwardDirection() const
		{
			return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
		}

		glm::quat EditorCamera::GetOrientation() const
		{
			return glm::quat(glm::vec3(-m_pitch, -m_yaw, 0.0f));
		}

		void EditorCamera::UpdateProjection()
		{
			m_aspect_ratio = m_viewport_size.x / m_viewport_size.y;
			m_projection_matrix = glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near, m_far);
		}

		void EditorCamera::UpdateView()
		{
			// For 2D perspective
			if (m_block_xyz)
			{
				m_yaw = m_pitch = 0.0f;
			}
			m_position = CalculatePosition();

			glm::quat orientation = GetOrientation();
			m_view_matrix = glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(orientation);
			m_view_matrix = glm::inverse(m_view_matrix);
		}

		bool EditorCamera::OnMouseScroll(MouseScrollEvent& e)
		{
			float delta = (float)e.GetYOffset() * 0.1f;
			MouseZoom(delta);
			UpdateView();
			return false;
		}

		void EditorCamera::MousePan(const glm::vec2& delta)
		{
			auto [xSpeed, ySpeed] = PanSpeed();
			m_focal_point += -GetRightDirection() * delta.x * xSpeed * m_distance;
			m_focal_point += GetUpDirection() * delta.y * ySpeed * m_distance;
		}

		void EditorCamera::MouseRotate(const glm::vec2& delta)
		{
			float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
			m_yaw += yawSign * delta.x * RotationSpeed();
			m_pitch += delta.y * RotationSpeed();
		}

		void EditorCamera::MouseZoom(float delta)
		{
			m_distance -= delta * ZoomSpeed();
			if (m_distance < 1.0f)
			{
				m_focal_point += GetForwardDirection();
				m_distance = 1.0f;
			}
		}

		glm::vec3 EditorCamera::CalculatePosition() const
		{
			return m_focal_point - GetForwardDirection() * m_distance;
		}

		std::pair<float, float> EditorCamera::PanSpeed() const
		{
			float x = std::min(m_viewport_size.x / 1000.0f, 2.4f); // max = 2.4f
			float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

			float y = std::min(m_viewport_size.y / 1000.0f, 2.4f); // max = 2.4f
			float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

			return { xFactor, yFactor };
		}

		float EditorCamera::RotationSpeed() const
		{
			return 0.8f;
		}

		float EditorCamera::ZoomSpeed() const
		{
			float distance = m_distance * 0.2f;
			distance = std::max(distance, 0.0f);
			float speed = distance * distance;
			speed = std::min(speed, 100.0f);
			return speed;
		}
	}
}
