#pragma once

#include "glophysx/core/core.h"
#include "xhash"

namespace GLOPHYSX {

	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_uuid; }

	private:
		uint64_t m_uuid;
	};
}
