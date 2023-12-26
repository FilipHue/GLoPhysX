#pragma once

#include "glophysx/components/scene/scene.h"
#include "glophysx/rendering/objects/texture/texture.h"

class EditorLayer;

namespace GLOPHYSX {

	using namespace RENDERING;
	using namespace COMPONENTS;

	namespace EDITOR {

		enum class SceneState
		{
			EDIT,
			PLAY,
			PAUSE,
			STOP
		};

		class ToolBar
		{
		public:
			ToolBar();

			void SetContext(Shared<Scene>& context);
			void Render();

		private:
			void OnScenePlay();
			void OnSceneStop();

		private:
			Shared<Scene> m_context;

			Shared<Texture2D> m_play_icon;
			Shared<Texture2D> m_pause_icon;
			Shared<Texture2D> m_stop_icon;

			SceneState m_scene_state = SceneState::EDIT;

			friend class EditorLayer;
		};
	}
}
