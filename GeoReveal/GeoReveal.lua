project "GeoReveal"
	if(staticBuild) then
		kind "StaticLib"
	else
		kind "SharedLib"
	end
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "")
	objdir ("bin-int/" .. outputdir .. "")
	
	pchheader "gv_pch.h"
	pchsource "src/gv_pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"%{dependencies}/glm/glm/**.hpp",
		"%{dependencies}/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}
	if(staticBuild == false) then
		defines
		{
			"GV_DYNAMIC_LINK",
			"GV_DLL_BUILD"
		}
	end

	includedirs
	{
		"src",
		"%{Dependencies}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
	}
	
	filter "system:windows"
		systemversion "latest"

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
		runtime "Release"
		optimize "on"
		symbols "off"
