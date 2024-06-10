#pragma once

namespace GLOPHYSX {

	namespace COMPONENTS {

		class ScriptableEntity;
		struct NativeScriptComponent
		{
			ScriptableEntity* m_instance = nullptr;
			char m_script_file[4096] = 
R"(
--[[
	Available functions:
		IsKeyPressed(int keycode)
		Translate(x, y, z)
		RotateZ(degrees)
		Scale(x, y)
	For key input use ascii codes (ex: 65 - A)
]]

function OnCreate()
end

function OnUpdate(deltaTime)
end

function OnDestroy()
end
)";

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
