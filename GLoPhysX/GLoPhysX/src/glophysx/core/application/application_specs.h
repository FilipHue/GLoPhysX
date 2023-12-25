#pragma once

#include <string>

namespace GLOPHYSX {

	struct CommandLineArgs
	{
		int m_cout;
		char** m_args = nullptr;

		const char* operator[](int index) const
		{
			return m_args[index];
		}
	};

	struct ApplicationSpecifications
	{
		std::string m_name;
		unsigned int m_width, m_height;

		std::string m_working_directory;
	};
}
