project "Pong"
   kind "ConsoleApp"
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
     "%{DepIncludeDir.MultiExtend}"
   }

   links
   {
     "Core",
     "SDL",
     "SDL_main",
     "MultiExtend"
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