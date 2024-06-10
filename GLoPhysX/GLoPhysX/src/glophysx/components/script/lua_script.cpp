#include "gxpch.h"
#include "lua_script.h"

#include "glophysx/core/input/input.h"
#include  "glophysx/core/input/keycodes.h"

#include "glophysx/components/script/scriptable_entity.h"

namespace GLOPHYSX {

	namespace COMPONENTS {

		LuaScript::LuaScript(const char* script_file, ScriptableEntity* e) : m_e(e)
        {
            L = luaL_newstate();
            luaL_openlibs(L);

            lua_register(L, "IsKeyPressed", IsKeyPressed);
            lua_register(L, "Translate", Translate);
            lua_register(L, "RotateZ", RotateZ);
            lua_register(L, "Scale", Scale);

            lua_pushlightuserdata(L, m_e);
            lua_setglobal(L, "entity");

            if (luaL_dostring(L, script_file) != LUA_OK) {
                std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
                lua_pop(L, 1);
            }
        }

        LuaScript::~LuaScript()
        {
            if (L) {
                lua_close(L);
            }
        }

        void LuaScript::OnCreate()
        {
            CallLuaFunction("OnCreate");
        }

        void LuaScript::OnUpdate(float deltaTime)
        {
            lua_getglobal(L, "OnUpdate");
            if (lua_isfunction(L, -1)) {
                lua_pushnumber(L, deltaTime);
                if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
                    std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
                    lua_pop(L, 1);
                }
            }
            else {
                lua_pop(L, 1);
            }
        }

        void LuaScript::OnDestroy()
        {
            CallLuaFunction("OnDestroy");
        }

        int LuaScript::IsKeyPressed(lua_State* L)
        {
            lua_Integer keycode = luaL_checkinteger(L, 1);
            bool is_pressed = Input::IsKeyPressed((int)keycode);
            lua_pushboolean(L, is_pressed);

            return 1;
        }

        int LuaScript::Translate(lua_State* L)
        {
            int args = lua_gettop(L);
            if (args != 3) {
                luaL_error(L, "translateObject requires 3 arguments (x, y, z)");
                return 0;
            }

            float x = static_cast<float>(luaL_checknumber(L, 1));
            float y = static_cast<float>(luaL_checknumber(L, 2));
            float z = static_cast<float>(luaL_checknumber(L, 3));

            lua_getglobal(L, "entity");
            ScriptableEntity* entity = static_cast<ScriptableEntity*>(lua_touserdata(L, -1));
            if (entity) {
                entity->GetComponent<TransformComponent>().m_translation += glm::vec3(x, y, z);
            }

            return 0;
        }

        int LuaScript::RotateZ(lua_State* L)
        {
            float rotation = static_cast<float>(luaL_checknumber(L, 1));

            lua_getglobal(L, "entity");
            ScriptableEntity* entity = static_cast<ScriptableEntity*>(lua_touserdata(L, -1));
            if (entity) {
                entity->GetComponent<TransformComponent>().m_rotation = glm::vec3(0.0, 0.0f, glm::radians(rotation));
            }

            return 0;
        }

        int LuaScript::Scale(lua_State* L)
        {
            int args = lua_gettop(L);

            float x = static_cast<float>(luaL_checknumber(L, 1));
            float y = static_cast<float>(luaL_checknumber(L, 2));

            lua_getglobal(L, "entity");
            ScriptableEntity* entity = static_cast<ScriptableEntity*>(lua_touserdata(L, -1));
            if (entity) {
                entity->GetComponent<TransformComponent>().m_scale += glm::vec3(x, y, 1.0f);
            }

            return 0;
        }

        void LuaScript::CallLuaFunction(const std::string& functionName)
        {
            lua_getglobal(L, functionName.c_str());
            if (lua_isfunction(L, -1)) {
                if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
                    std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
                    lua_pop(L, 1);
                }
            }
            else {
                lua_pop(L, 1);
            }
        }
	}
}