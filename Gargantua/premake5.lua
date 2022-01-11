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
		"%{wks.location}/Gargantua/vendor/glfw/include"
	}

	links {"glfw", "opengl32.lib"}


	filter "configurations:Debug"
		defines "GRG_DEBUG"
		symbols "On"


	filter "configurations:Release"
		defines "GRG_RELEASE"
		optimize "On"
		--buildoptions "/MT"