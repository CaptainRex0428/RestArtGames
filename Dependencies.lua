

DepIncludeDir={}

DepIncludeDir["SDL"] = PreRoot.MultiExtendDependenciesRoot.."/SDL/include"
DepIncludeDir["SDL_image"] = PreRoot.MultiExtendDependenciesRoot.."/SDL_image/include"

DepIncludeDir["glad"] = PreRoot.MultiExtendDependenciesRoot.."/glad/include"
DepIncludeDir["glfw"] = PreRoot.MultiExtendDependenciesRoot.."/glfw/include"
DepIncludeDir["glew"] = PreRoot.MultiExtendDependenciesRoot.."/glew/include/GL"
DepIncludeDir["imgui"] = PreRoot.MultiExtendDependenciesRoot.."/imgui"
 
DepIncludeDir["zlib"] = PreRoot.MultiExtendDependenciesRoot.."/zlib"
DepIncludeDir["libpng"] = PreRoot.MultiExtendDependenciesRoot.."/libpng"

DepIncludeDir["dlg"] = PreRoot.MultiExtendDependenciesRoot.."/dlg/include"
DepIncludeDir["freetype"] = PreRoot.MultiExtendDependenciesRoot.."/freetype/include"
DepIncludeDir["harfbuzz"] = PreRoot.MultiExtendDependenciesRoot.."/harfbuzz/src"
DepIncludeDir["SDL_ttf"] = PreRoot.MultiExtendDependenciesRoot.."/SDL_ttf"

DepIncludeDir["spdlog"] = PreRoot.MultiExtendDependenciesRoot.."/spdlog/include"

DepIncludeDir["linmath"] = PreRoot.MultiExtendDependenciesRoot.."/linmath"

DepIncludeDir["lua"] = PreRoot.MultiExtendDependenciesRoot.."/lua"

DepIncludeDir["luacrypto"] = PreRoot.MultiExtendDependenciesRoot.."/luacrypto/src"
DepIncludeDir["openssl"] = PreRoot.MultiExtendDependenciesRoot.."/openssl/include"
DepIncludeDir["cryptopp"] = PreRoot.MultiExtendDependenciesRoot.."/cryptopp"

LibDirectories = {}
LibDirectories["openssl"] =  PreRoot.MultiExtendDependenciesRoot.."/openssl/lib"
LibDirectories["SDL_ttf"] =  LibDir.."/SDL_ttf"
LibDirectories["glfw"] =  LibDir.."/glfw"
LibDirectories["glad"] =  LibDir.."/glad"
LibDirectories["glew"] =  LibDir.."/glew"
LibDirectories["lua"] =  LibDir.."/lua"

Library = {}

ProjIncludeDir={}
ProjIncludeDir["MultiExtend"] = PreRoot.ExtensionRoot.."/MultiExtend/include"

