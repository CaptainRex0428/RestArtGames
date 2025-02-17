include "Directory.lua"
include "Dependencies.lua"

workspace "RestArtGames"
	architecture "x64"
	startproject "Render"
	configurations{
		"Debug",
		"Release",
        "Dist"
	}

    filter "system:windows"
    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/utf-8" }
	
group "Render"
	include "Render/Render.lua"

group "Extend"
	include "Extend/MultiExtend/MultiExtend.lua"
	
group "Dependencies"
	include "Dependencies/SDL.lua"
	include "Dependencies/SDL_image.lua"
	include "Dependencies/glad.lua"
	include "Dependencies/glfw.lua"
	include "Dependencies/glew.lua"
	include "Dependencies/imgui.lua"
	include "Dependencies/libpng.lua"
	include "Dependencies/zlib.lua"

	include "Dependencies/dlg.lua"
	include "Dependencies/freetype.lua"
	include "Dependencies/harfbuzz.lua"
	include "Dependencies/SDL_ttf.lua"

	include "Dependencies/spdlog.lua"
	
group "Dependencies/Examples"
	include "Dependencies/SDL_image_Example.lua"
	include "Dependencies/dlg_example.lua"
	include "Dependencies/SDL_ttf_Example.lua"

group "Games"
   include "Games/Pong/Pong.lua"
   include "Games/SpriteShip/SpriteShip.lua"

group ""
   include "App/App.lua"