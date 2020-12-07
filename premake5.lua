workspace "Tests"
	architecture "x64"
	startproject "VectorTest"

	configurations
	{
		"Debug",
		"Release"
	}

	platforms { "Win32", "Win64" }

	filter { "platforms:Win32" }
		system "Windows"
		architecture "x86"

	filter { "platforms:Win64" }
		system "Windows"
		architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Project list here

project "VectorTest"
	kind "ConsoleApp"
	language "C++"
	location "VectorTest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/obj/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp" 
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines {"DEBUG"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines {"NDEBUG"}
		runtime "Release"
		optimize "on"

-- ==============================================

project "ArrayTest"
	kind "ConsoleApp"
	language "C++"
	location "ArrayTest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/obj/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp" 
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines {"DEBUG"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines {"NDEBUG"}
		runtime "Release"
		optimize "on"

-- ==============================================