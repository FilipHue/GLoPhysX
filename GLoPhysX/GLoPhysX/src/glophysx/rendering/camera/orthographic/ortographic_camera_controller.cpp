#include "gxpch.h"
#include "ortographic_camera_controller.h"

#include "glophysx/core/input/input.h"
#include "glophysx/core/input/keycodes.h"

namespace GLOPHYSX {

	namespace RENDERING {

		OrthographicCameraController::OrthographicCameraController(float aspect_ration) :
			m_aspect_ration(aspect_ration),
			m_camera(-m_aspect_ration * m_zoom, m_aspect_ration* m_zoom, -m_zoom, m_zoom)
		{
		}

		void OrthographicCameraController::OnUpdate(DeltaTime dt)
		{
			if (Input::IsKeyPressed(GLOP_KEY_A)) {
				m_camera_position.x -= m_camera_translation_speed * m_zoom * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_D)) {
				m_camera_position.x += m_camera_translation_speed * m_zoom * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_W)) {
				m_camera_position.y += m_camera_translation_speed * m_zoom * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_S)) {
				m_camera_position.y -= m_camera_translation_speed * m_zoom * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_Q)) {
				m_camera_rotation -= m_camera_rotation_speed * m_zoom * dt;
			}

			if (Input::IsKeyPressed(GLOP_KEY_E)) {
				m_camera_rotation += m_camera_rotation_speed * m_zoom * dt;
			}

			m_camera.SetPosition(m_camera_position);
			m_camera.SetRotation(m_camera_rotation);
		}
		void OrthographicCameraController::OnEvent(Event& e)
		{
			EventDispatcher::Dispatch<MouseScrollEvent>(e, std::bind(&OrthographicCameraController::OnMouseScroll, this, std::placeholders::_1));
			EventDispatcher::Dispatch<WindowResizeEvent>(e, std::bind(&OrthographicCameraController::OnWindowResize, this, std::placeholders::_1));
		}
		bool OrthographicCameraController::OnMouseScroll(MouseScrollEvent& e)
		{
			m_zoom -= (int)e.GetYOffset() * m_zoom_smoothstep;
			if (m_zoom < m_zoom_min) {
				m_zoom = m_zoom_min;
			}

			m_camera.SetProjection(-m_aspect_ration * m_zoom, m_aspect_ration * m_zoom, -m_zoom, m_zoom);

			return false;
		}
		bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
		{
			m_aspect_ration = (float)e.GetWidth() / (float)e.GetHeight();

			m_camera.SetProjection(-m_aspect_ration * m_zoom, m_aspect_ration * m_zoom, -m_zoom, m_zoom);

			return false;
		}
	}
}
