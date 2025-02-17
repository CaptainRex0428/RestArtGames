project "Game"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp","include/**.h","include/**.cpp" }

   includedirs
   {
     "src",
     "include",

     "%{DepIncludeDir.core}",
     "%{DepIncludeDir.SDL}",
     "%{DepIncludeDir.SDL_image}"
  
   }

   links
   {
     "Core",
     "SDL",
     "SDL_main",
     "SDL_image"
   }
   
   location (LocationDir)
   targetdir (TargetDir)
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
       optimize "Speed"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"