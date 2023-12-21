#include "gxpch.h"
#include "entity.h"

namespace GLOPHYSX {

	namespace COMPONENTS {

		Entity::Entity(entt::entity handle, Scene* scene) : m_entity_handle(handle), m_scene(scene)
		{
		}
	}
}
