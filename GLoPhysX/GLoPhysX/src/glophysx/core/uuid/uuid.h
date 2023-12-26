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

// Custom hash function for UUID class
namespace std {

	template<>
	struct hash<GLOPHYSX::UUID>
	{
		std::size_t operator()(const GLOPHYSX::UUID& uuid) const
		{
			return hash<uint64_t>()(uuid);
		}
	};
}
