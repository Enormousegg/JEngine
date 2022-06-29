workspace "JEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Engine/vendor/Glad/include"
IncludeDir["Imgui"] = "Engine/vendor/Imgui"
IncludeDir["glm"] = "Engine/vendor/glm"

include "Engine/vendor/Glad"
include "Engine/vendor/Imgui"

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir("bin/" ..outputdir.."/%{prj.name}")
	objdir("bin-int/" ..outputdir.."/%{prj.name}")

	pchheader "egpch.h"
	pchsource "Engine/src/egpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"Engine/vendor/GLFW/lib"
	}

	links
	{	
		"glfw3_mt.lib",
		"Glad",
		"Imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.19041.0"

		defines--预处理命令
		{
			"EG_PLATFORM_WINDOWS",
			"EG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		--生成的dll文件复制到Sandbox
		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} \"../bin/"..outputdir.."/Sandbox/\""
			--"{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		runtime "Debug"
		--buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "EG_Release"
		runtime "Release"
		--buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "EG_Dist"
		runtime "Release"
		--buildoptions "/MD"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleAPP"
	language "C++"
	staticruntime "off"

	targetdir("bin/" ..outputdir.."/%{prj.name}")
	objdir("bin-int/" ..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/src",
		"%{IncludeDir.glm}"
	}

	links
	{	
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.19041.0"

		defines--预处理命令
		{
			"EG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		runtime "Debug"
		--buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "EG_Release"
		runtime "Release"
		--buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "EG_Dist"
		runtime "Release"
		--buildoptions "/MD"
		optimize "on"