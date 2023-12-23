#pragma once

#include <string>

#include <commdlg.h>
#include "glophysx/core/application/application.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3native.h"


namespace GLOPHYSX {

	namespace PLATFORM {

		class FileDialogs
		{
		public:
			static std::string SaveFile(const char* filter);
			static std::string OpenFile(const char* filter);

		private:
		};

		std::string FileDialogs::SaveFile(const char* filter)
		{
#ifdef GLOP_PLATFORM_WINDOWS
			OPENFILENAMEA ofn;
			CHAR sz_file[260] = { 0 };
			CHAR currentDir[256] = { 0 };

			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::GetInstance().GetWindow().GetNativeWindow());
			ofn.lpstrFile = sz_file;
			ofn.nMaxFile = sizeof(sz_file);
			if (GetCurrentDirectoryA(256, currentDir))
				ofn.lpstrInitialDir = currentDir;
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

			ofn.lpstrDefExt = strchr(filter, '\0') + 1;

			if (GetSaveFileNameA(&ofn) == TRUE)
				return ofn.lpstrFile;

			return std::string();
#else
#error GLoPhysX only supports Windows
#endif
		}

		std::string FileDialogs::OpenFile(const char* filter)
		{
#ifdef GLOP_PLATFORM_WINDOWS
			OPENFILENAMEA ofn;
			CHAR sz_file[260] = { 0 };

			ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::GetInstance().GetWindow().GetNativeWindow());
			ofn.lpstrFile = sz_file;
			ofn.nMaxFile = sizeof(sz_file);
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				return ofn.lpstrFile;
			}

			return std::string();
#else
#error GLoPhysX only supports Windows
#endif
		}
	}
}
