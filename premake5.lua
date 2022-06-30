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

include "Engine/vendor/GLFW"
include "Engine/vendor/Glad"
include "Engine/vendor/Imgui"

project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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

	--libdirs
	--{
		--"%{prj.name}/vendor/GLFW/lib"
	--}

	links
	{	
		"Glad",
		"Imgui",
		"opengl32.lib",
		"GLFW"
	}

	filter "system:windows"
		systemversion "latest"

		defines--预处理命令
		{
			"EG_PLATFORM_WINDOWS",
			"EG_BUILD_DLL",
			"GLFW_INCLUDE_NONE",--防止重复包含
			"_CRT_SECURE_NO_WARNINGS"--去除scanf警告
		}

		--生成的dll文件复制到Sandbox
		--postbuildcommands
		--{
			--"{COPY} %{cfg.buildtarget.relpath} \"../bin/"..outputdir.."/Sandbox/\""
			--"{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox"
		--}

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
	cppdialect "C++17"
	staticruntime "on"

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
		"Engine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{	
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

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