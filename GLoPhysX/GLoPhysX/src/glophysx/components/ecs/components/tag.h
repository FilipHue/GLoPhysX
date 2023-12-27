#pragma once

#include <string>

namespace GLOPHYSX {

	namespace COMPONENTS {

		struct TagComponent
		{
			std::string m_tag;

			TagComponent() = default;
			TagComponent(const TagComponent&) = default;
			TagComponent(const std::string& tag) : m_tag(tag) {}
		};
	}
}
