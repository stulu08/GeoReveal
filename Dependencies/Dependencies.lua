
if InstallDir == nil or InstallDir == '' then
	InstallDir = "%{wks.location}";
end

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
Dependencies = "%{InstallDir}/Dependencies"

ProjectDir = {}
ProjectDir["GeoReveal"] = "%{InstallDir}/GeoReveal"
ProjectDir["Discord"] = "%{Dependencies}/discord-game-sdk/"

LibraryDir = {}
LibraryDir["Discord"] = "%{ProjectDir.Discord}/lib/%{cfg.architecture}"

Library = {}
Library["GeoReveal"] = "GeoReveal.lib"
Library["OpenGL"] = "opengl32.lib"
Library["Discord"] = "discord_game_sdk.dll"
Library["DiscordLib"] = "discord_game_sdk.dll-lib"

IncludeDir = {}
IncludeDir["GeoReveal"] = "%{ProjectDir.GeoReveal}/src"
IncludeDir["spdlog"] = "%{Dependencies}/spdlog/include"
IncludeDir["GLFW"] = "%{Dependencies}/GLFW/include"
IncludeDir["Glad"] = "%{Dependencies}/Glad/include"
IncludeDir["ImGui"] = "%{Dependencies}/imgui"
IncludeDir["glm"] = "%{Dependencies}/glm"
IncludeDir["stb_image"] = "%{Dependencies}/stb_image"
IncludeDir["Discord"] = "%{ProjectDir.Discord}/cpp"