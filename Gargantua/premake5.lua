project "Gargantua"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "On"
	systemversion "latest"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {"src/**.hpp", "src/**.cpp", "test/**.hpp", "test/**.cpp"}

	--include dirs extern to project do not work. i don't know if is is a bug from visual studio or premake.
	includedirs 
	{
		"src",
		"%{wks.location}/Gargantua/vendor/glfw/include",
		"%{wks.location}/Gargantua/vendor/Glad/include",
		"%{wks.location}/Gargantua/vendor/imgui",
		"%{wks.location}/Gargantua/vendor/stb_image",
	}

	links {"ImGui", "Glad", "glfw", "opengl32.lib", "stb_image"}

	--defines {"GRG_LOGGER_ON"}

	filter "configurations:Debug"
		defines "GRG_MODE_DEBUG"
		runtime "Debug"
		symbols "On"


	filter "configurations:Release"
		defines "GRG_MODE_RELEASE"
		runtime "Release"
		optimize "On"