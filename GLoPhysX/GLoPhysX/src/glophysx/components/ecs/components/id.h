#pragma once

#include "glophysx/core/uuid/uuid.h"

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct IDComponent
		{
			UUID m_id;

			IDComponent() = default;
			IDComponent(const IDComponent&) = default;
			IDComponent(UUID uuid)
			{
				m_id = uuid;
			}
		};
	}
}
