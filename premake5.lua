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

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
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
		symbols "on"

	filter "configurations:Release"
		defines "EG_Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EG_Dist"
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
		"Engine/src"
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
		symbols "on"

	filter "configurations:Release"
		defines "EG_Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EG_Dist"
		optimize "on"