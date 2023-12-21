workspace "GLoPhysX"
	architecture "x64"
	startproject "GLoPhysX-Editor"

	configurations
	{
		"Debug",
		"Release"
	}

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GLoPhysX"
	location "GLoPhysX"

	-- USE StaticLib IF YOU WANT TO LINK AGAINST THE STATIC LIBRARY --
	-- USE SharedLib IF YOU WANT TO LINK AGAINST THE DYNAMIC LIBRARY --

	kind "StaticLib"
	-- kind "SharedLib"

	------------------------------------------------------------------

	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"%{prj.name}/dependencies/GLM/**.inl",

		"%{prj.name}/dependencies/STB/**.h",
		"%{prj.name}/dependencies/STB/**.cpp",

		"%{prj.name}/dependencies/ENTT/entt/**.h"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/dependencies/SPDLOG",
		"%{prj.name}/dependencies/GLFW/include",
		"%{prj.name}/dependencies/GLAD/include",
		"%{prj.name}/dependencies/IMGUI",
		"%{prj.name}/dependencies/GLM",
		"%{prj.name}/dependencies/STB",
		"%{prj.name}/dependencies/ENTT"
	}

	libdirs
	{
		"%{prj.name}/dependencies/GLFW"
	}

	links
	{
		"glfw3.lib",
		"opengl32.lib"
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
		systemversion "latest"

		-- USE ONLY GLOP_PLATFORM_WINDOWS IF YOU WANT TO LINK AGAINST THE STATIC LIBRARY --
		-- USE GLOP_PLATFORM_WINDOWS, GLOP_DYNAMIC_LIB AND GLOP_BUILD_DLL IF YOU WANT TO LINK AGAINST THE DYNAMIC LIBRARY --

		defines
		{
			"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING", -- For MSVC stdext::checked_array_iterator<T*> error (will be removed in the future)
			"GLOP_PLATFORM_WINDOWS"
		}

		-- defines
		-- {
		-- 	"GLOP_PLATFORM_WINDOWS",
		-- 	"GLOP_DYNAMIC_LIB",
		-- 	"GLOP_BUILD_DLL"
		-- }

		----------------------------------------------------------------------------------------------



		-- COMMENT THIS IF YOU WANT TO LINK AGAINST THE STATIC LIBRARY --

		-- postbuildcommands
		-- {
		-- 	("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. output_dir .. "/Sandbox")
		-- }

		------------------------------------------------------------------

	filter "configurations:Debug"
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
	cppdialect "C++17"
	staticruntime "off"

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
		"GLoPhysX/dependencies/GLM",
		"GLoPhysX/dependencies/STB",
		"GLoPhysX/dependencies/ENTT"
	}

	-- UNCOMMENT THIS IF YOU WANT TO LINK AGAINST THE STATIC LIBRARY --

	linkoptions
	{ 
		"/NODEFAULTLIB:MSVCRT.lib"
	}

	--------------------------------------------------------------------

	links
	{
		"GLoPhysX"
	}

	filter "system:windows"
		systemversion "latest"

		-- USE ONLY GLOP_PLATFORM_WINDOWS IF YOU WANT TO LINK AGAINST THE STATIC LIBRARY --
		-- USE GLOP_PLATFORM_WINDOWS AND GLOP_DYNAMIC_LIB IF YOU WANT TO LINK AGAINST THE DYNAMIC LIBRARY --

		defines
		{
			"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING", -- For MSVC stdext::checked_array_iterator<T*> (will be removed in the future)
			"GLOP_PLATFORM_WINDOWS"
		}

		-- defines
		-- {
		-- 	"GLOP_PLATFORM_WINDOWS",
		-- 	"GLOP_DYNAMIC_LIB"
		-- }

		-----------------------------------------------------------------------------------

	filter "configurations:Debug"
		runtime "Debug"
		defines "GLOP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GLOP_RELEASE"
		optimize "On"

project "GLoPhysX-Editor"
	location "GLoPhysX-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"GLoPhysX/dependencies/GLM",
		"GLoPhysX/dependencies/STB",
		"GLoPhysX/dependencies/ENTT"
	}

	-- UNCOMMENT THIS IF YOU WANT TO LINK AGAINST THE STATIC LIBRARY --

	linkoptions
	{ 
		"/NODEFAULTLIB:MSVCRT.lib"
	}

	--------------------------------------------------------------------

	links
	{
		"GLoPhysX"
	}

	filter "system:windows"
		systemversion "latest"

		-- USE ONLY GLOP_PLATFORM_WINDOWS IF YOU WANT TO LINK AGAINST THE STATIC LIBRARY --
		-- USE GLOP_PLATFORM_WINDOWS AND GLOP_DYNAMIC_LIB IF YOU WANT TO LINK AGAINST THE DYNAMIC LIBRARY --

		defines
		{
			"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING", -- For MSVC stdext::checked_array_iterator<T*> (will be removed in the future)
			"GLOP_PLATFORM_WINDOWS"
		}

		-- defines
		-- {
		-- 	"GLOP_PLATFORM_WINDOWS",
		-- 	"GLOP_DYNAMIC_LIB"
		-- }

		-----------------------------------------------------------------------------------

	filter "configurations:Debug"
		runtime "Debug"
		defines "GLOP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GLOP_RELEASE"
		optimize "On"
