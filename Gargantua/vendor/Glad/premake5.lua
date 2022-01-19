project "Glad"
	kind "StaticLib"
	language "C"
	systemversion "latest"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/khr/khrplatform.h",
		"src/glad.c",
	}

	includedirs {"include"}


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		runtime "Release"
		optimize "on"