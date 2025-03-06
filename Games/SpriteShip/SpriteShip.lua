project "SpriteShip"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp","include/**.h","include/**.cpp","assets/**" }

   includedirs
   {
     "src",
     "include",

     "%{ProjIncludeDir.MultiExtend}",
     "%{DepIncludeDir.SDL}",
     "%{DepIncludeDir.SDL_image}",
     "%{DepIncludeDir.spdlog}",
     "%{DepIncludeDir.cryptopp}"
   }

   links
   {
     "MultiExtend",
     "SDL",
     "SDL_main",
     "SDL_image",

     "spdlog",
     "cryptopp"
     
   }
   
   location (LocationDir)
   targetdir (EXEDir)
   objdir (ObjectDir)

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"