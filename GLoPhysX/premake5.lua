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

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/dependencies/SPDLOG/"
	}

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
		"GLoPhysX/dependencies/SPDLOG",
		"GLoPhysX/src"
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
		runtime "Debug"
		defines "GLOP_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GLOP_RELEASE"
		optimize "On"