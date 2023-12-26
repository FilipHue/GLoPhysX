#include "gxpch.h"
#include "uuid.h"

#include <random>

namespace GLOPHYSX {

	static std::random_device s_random_device;
	static std::mt19937_64 s_engine(s_random_device());
	static std::uniform_int_distribution<uint64_t> s_uniform_distribution;

	UUID::UUID()
	{
		m_uuid = s_uniform_distribution(s_engine);
	}

	UUID::UUID(uint64_t uuid)
	{
		m_uuid = uuid;
	}
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
