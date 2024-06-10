#pragma once

#include "glophysx/components/ecs/entity.h"

#include "glophysx/components/script/lua_script.h"

namespace GLOPHYSX {

	namespace COMPONENTS {

		class ScriptableEntity
		{
		public:
			virtual ~ScriptableEntity() {};

			template<typename T>
			T& GetComponent() {
				return m_entity.GetComponent<T>();
			}

		protected:
			virtual void OnCreate() {}
			virtual void OnUpdate(DeltaTime dt) {}
			virtual void OnDestroy() {}

			void InitLua(const char* m_script_path)
			{
				m_lua_script = new LuaScript(m_script_path, this);
			}

		protected:
			LuaScript* m_lua_script;

		private:
			Entity m_entity;

			friend class Scene;
			friend class LuaScript;
		};
	}
}
