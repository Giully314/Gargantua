project "STLHeaderUnit"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    systemversion "latest"
    compileas "Module"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {"library.cpp"}

    filter "configurations:Debug"
      symbols "On"
      buildoptions {"/MDd /EHsc /translateInclude" }


   filter "configurations:Release"
      optimize "On"
      buildoptions {"/MD /EHsc /translateInclude"}