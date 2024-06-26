#pragma once

#include "glophysx/core/events/event.h"
#include "glophysx/core/events/mouse_events.h"
#include "glophysx/core/events/application_events.h"
#include "glophysx/core/time/time.h"

#include "orthographic_camera.h"

namespace GLOPHYSX {

	namespace RENDERING {


		class OrthographicCameraController
		{
		public:
			OrthographicCameraController(float aspect_ration);

			void OnUpdate(DeltaTime dt);
			void OnEvent(Event& e);

			void OnViewportResize(uint32_t width, uint32_t height);

			void SetZoom(float zoom) { m_zoom = zoom; }
			float GetZoom() const { return m_zoom; }

			OrthographicCamera& GetCamera() { return m_camera; }
			const OrthographicCamera& GetCamera() const { return m_camera; }

		private:
			bool OnMouseScroll(MouseScrollEvent& e);
			bool OnWindowResize(WindowResizeEvent& e);

		private:
			float m_aspect_ration;
			float m_zoom = 1.0f;
			OrthographicCamera m_camera;

			glm::vec3 m_camera_position = glm::vec3(0.f, 0.f, 0.f);
			float m_camera_rotation = 0.f;
			float m_camera_translation_speed = 2.5f;
			float m_camera_rotation_speed = 180.f;

			float m_zoom_smoothstep = 0.5f;
			float m_zoom_min = 0.25f;
		};
	}
}
