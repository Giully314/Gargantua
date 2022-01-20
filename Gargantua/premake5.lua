project "Gargantua"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "On"
	systemversion "latest"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {"src/**.hpp", "src/**.cpp", "test/**.hpp", "test/**.cpp"}

	includedirs 
	{
		"src",
		"%{wks.location}/Gargantua/vendor/glfw/include",
		"%{wks.location}/Gargantua/vendor/Glad/include"
	}

	links {"Glad", "glfw", "opengl32.lib"}

	--defines {"GRG_LOGGER_ON"}

	filter "configurations:Debug"
		defines "GRG_MODE_DEBUG"
		runtime "Debug"
		symbols "On"


	filter "configurations:Release"
		defines "GRG_MODE_RELEASE"
		runtime "Release"
		optimize "On"