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

group "Extension"
	include(path.join(PreRoot.ExtensionRoot, "MultiExtend/MultiExtend.lua"))
	
group "Dependencies"
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "lua.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "dlg.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "freetype.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "harfbuzz.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "spdlog.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "imgui.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "libpng.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "zlib.lua"))
	
group "Dependencies/SDL"
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "SDL.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "SDL_image.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "SDL_ttf.lua"))
	
group "Dependencies/crypto"
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "cryptopp.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "luacrypto.lua"))
	
group "Dependencies/OpenGL"
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "glad.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "glfw.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "glew.lua"))
	
group "Dependencies/Examples"
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "SDL_image_Example.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "dlg_example.lua"))
	include(path.join(PreRoot.MultiExtendDependenciesRoot, "SDL_ttf_Example.lua"))

group "Games"
   include "Games/Pong/Pong.lua"
   include "Games/SpriteShip/SpriteShip.lua"

group ""
   include "App/App.lua"

