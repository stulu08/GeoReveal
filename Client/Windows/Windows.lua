project "Windows Client"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "")
	objdir ("bin-int/" .. outputdir .. "")
	
	pchheader "gv_pch.h"
	pchsource "src/pch.cpp"
	
	defines
	{
		"GV_WINDOWS_CLIENT",
		"_CRT_SECURE_NO_WARNINGS"
	}
	if(staticBuild == false) then
		defines
		{
			"GV_DYNAMIC_LINK",
		}
	end

	files
	{
		"src/**.h",
		"src/**.cpp",
		
		"%{dependencies}/stb_image/**.cpp",
		"%{dependencies}/stb_image/**.h",
	}

	includedirs
	{
		"src",
		"%{Dependencies}",
		"%{IncludeDir.GeoReveal}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Discord}",
		"%{IncludeDir.stb_image}",
	}
	links
	{
		"GeoReveal", 
		"Discord C++ Game SDK",
		"GLFW",
		"Glad",
		"ImGui",

		"%{Library.OpenGL}"
	}


	filter "system:windows"
		systemversion "latest"
		defines
		{
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GV_DEBUG"
		runtime "Debug"
		optimize "off"
		symbols "on"

	filter "configurations:Release"
		defines "GV_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "on"

	filter "configurations:Dist"
		defines "GV_DIST"
		kind "WindowedApp"
		runtime "Release"
		optimize "on"
		symbols "off"
