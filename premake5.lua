workspace "Leaf"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Includes for 3rd party libraries
IncludeDir = {}
IncludeDir["GLFW"] = "Leaf/vendor/GLFW/include"
IncludeDir["Glad"] = "Leaf/vendor/Glad/include"
IncludeDir["ImGui"] = "Leaf/vendor/ImGui"
IncludeDir["glm"] = "Leaf/vendor/glm"

group "Libraries" 
	include "Leaf/vendor/GLFW"
	include "Leaf/vendor/Glad"
	include "Leaf/vendor/ImGui"
group ""

project "Leaf"
	location "Leaf"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lfpch.h"
	pchsource "Leaf/src/lfpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src/",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LF_PLATFORM_WINDOWS",
			"LF_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"LF_ASSERTS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "LF_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "LF_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "LF_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "Off"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Leaf/vendor/spdlog/include",
		"Leaf/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Leaf"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LF_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LF_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "LF_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "LF_DIST"
		runtime "Release"
		optimize "On"