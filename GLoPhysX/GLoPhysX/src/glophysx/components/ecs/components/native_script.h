#pragma once

namespace GLOPHYSX {

	namespace COMPONENTS {

		class ScriptableEntity;
		struct NativeScriptComponent
		{
			ScriptableEntity* m_instance = nullptr;

			ScriptableEntity* (*InstantiateScript)();
			void(*DestroyScript)(NativeScriptComponent*);

			template<typename T>
			void Bind()
			{
				InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
				DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->m_instance; nsc->m_instance = nullptr; };
			}

			NativeScriptComponent() = default;
			NativeScriptComponent(const NativeScriptComponent&) = default;
		};
	}
}
