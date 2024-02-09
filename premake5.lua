include "./Dependencies/premake/premake_customization/solution_items.lua"
include "./Dependencies/premake/premake_customization/generate_doc.lua"
workspace "GeoReveal"
	startproject "WindowsClient"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	flags
	{
		"MultiProcessorCompile"
	}
	solution_items 
	{
		"premake5.lua",
		"Dependencies/Dependencies.lua",
		"GeoReveal/GeoReveal.lua",
		"Client/Windows/Windows.lua",
		"README.md"
	}
	architecture "x86_64"

	filter "configurations:Debug"
		defines     "_DEBUG"

	filter "configurations:Release or Dist"
		defines     "NDEBUG"

	filter { "system:windows", "configurations:Dist", "toolset:not mingw" }
		flags		{ "LinkTimeOptimization" }
	
	filter "action:vs*"
		linkoptions {
			"/ignore:4006",
			"/ignore:4099",
			"/ignore:4251",
			"/ignore:4996",
		}
		disablewarnings {
			"4006",
			"4099",
			"4251",
			"4996",
		}

staticBuild = true

include "Dependencies/Dependencies.lua"

group "Dependencies"
include "Dependencies/GLFW"
include "Dependencies/Glad"
include "Dependencies/imgui"
include "Dependencies/discord-game-sdk/CPP SDK.lua"
group "Client"
include "Client/Windows/Windows.lua"
group ""
include "GeoReveal/GeoReveal.lua"
