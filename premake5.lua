workspace "JEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" ..outputdir.."/%{prj.name}")
	objdir("bin-int/" ..outputdir.."/%{prj.name}")

	pchheader "egpch.h"
	pchsource "Engine/src/egpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{prj.name}/vendor/GLFW/include"
	}

	libdirs
	{
		"%{prj.name}/vendor/GLFW/lib"
	}

	links
	{	
		"glfw3_mt",
		"opengl32"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "10.0.19041.0"

		defines--预处理命令
		{
			"EG_PLATFORM_WINDOWS",
			"EG_BUILD_DLL"
		}

		--生成的dll文件复制到Sandbox
		postbuildcommands
		{
			--"{COPY} %{cfg.buildtarget.relpath} ../bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Sandbox"
			"{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "EG_Release"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "EG_Dist"
		buildoptions "/MD"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleAPP"
	language "C++"

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
		"%{prj.name}/src"
	}

	links
	{	
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "10.0.19041.0"

		defines--预处理命令
		{
			"EG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "EG_Release"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "EG_Dist"
		buildoptions "/MD"
		optimize "on"