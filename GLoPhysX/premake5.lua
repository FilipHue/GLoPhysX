workspace "GLoPhysX"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GLoPhysX"
	location "GLoPhysX"
	kind "SharedLib"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. output_dir .. "/%{prj.name}")

	pchheader "gxpch.h"
	pchsource "GLoPhysX/src/gxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/dependencies/GLAD/include/glad.c",
		"%{prj.name}/dependencies/GLAD/include/glad/**.h",
		"%{prj.name}/dependencies/GLAD/include/KHR/**.h",
		"%{prj.name}/dependencies/IMGUI/**.h",
		"%{prj.name}/dependencies/IMGUI/**.cpp",
		"%{prj.name}/dependencies/GLM/**.hpp",
		"%{prj.name}/dependencies/GLM/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/dependencies/SPDLOG",
		"%{prj.name}/dependencies/GLFW/include",
		"%{prj.name}/dependencies/GLAD/include",
		"%{prj.name}/dependencies/IMGUI",
		"%{prj.name}/dependencies/GLM"
	}

	libdirs
	{
		"%{prj.name}/dependencies/GLFW"
	}

	links
	{
		"glfw3.lib",
		"opengl32.lib",
		"Shell32.lib",
		"User32.lib",
		"Gdi32.lib"
	}

	linkoptions
	{ 
		"/NODEFAULTLIB:MSVCRT.lib"
	}

	filter "files:**.c"
        flags { "NoPCH" }

	filter  "files:GLoPhysX/dependencies/IMGUI/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GLOP_PLATFORM_WINDOWS",
			"GLOP_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. output_dir .. "/Sandbox")
		}

	filter "configurations:Debug"
		staticruntime "off"
		runtime "Debug"
		defines "GLOP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GLOP_RELEASE"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. output_dir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. output_dir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"GLoPhysX/src",
		"GLoPhysX/dependencies/SPDLOG",
		"GLoPhysX/dependencies/GLFW/include",
		"GLoPhysX/dependencies/GLAD/include",
		"GLoPhysX/dependencies/IMGUI",
		"GLoPhysX/dependencies/GLM"
	}

	links
	{
		"GLoPhysX"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GLOP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		staticruntime "off"
		runtime "Debug"
		defines "GLOP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GLOP_RELEASE"
		optimize "On"