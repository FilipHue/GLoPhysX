#pragma once

#include "lua.hpp"

namespace GLOPHYSX {
    namespace COMPONENTS {
        class ScriptableEntity;
    }
}

namespace GLOPHYSX {

	namespace COMPONENTS {

		class LuaScript
		{
        public:
            LuaScript(const char* script_file, ScriptableEntity* e);

            ~LuaScript();

            void OnCreate();
            void OnUpdate(float deltaTime);
            void OnDestroy();

        private:
            static int IsKeyPressed(lua_State* L);
            static int Translate(lua_State* L);
            static int RotateZ(lua_State* L);
            static int Scale(lua_State* L);

            void CallLuaFunction(const std::string& functionName);

        private:
            lua_State* L;
            ScriptableEntity* m_e;
		};
	}
}

