project "Gargantua"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"


	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {"src/**.ixx", "src/**.cpp"}

	--technically the c++20 version specify the modules so it is not necessary to specify

	--include dirs extern to project do not work. i don't know if is is a bug from visual studio or premake.
	includedirs 
	{
		"src",
		"%{wks.location}/Gargantua/vendor/glfw/include",
		"%{wks.location}/Gargantua/vendor/Glad/include",
		"%{wks.location}/Gargantua/vendor/imgui",
		"%{wks.location}/Gargantua/vendor/stb_image",
	}

	links {"STLHeaderUnit", "imgui", "Glad", "glfw", "opengl32.lib", "stb_image"}


	filter "files:**.cpp"
		compileas "C++"

	filter "files:**.ixx"
		compileas "Module"


	filter "configurations:Debug"
		defines {"GRG_MODE_DEBUG", "GRG_LOGGER_ON"}
		symbols "On"
		buildoptions "/MDd /EHsc"
		files {"test/**.ixx", "test/**.cpp"}


	filter "configurations:Release"
		defines "GRG_MODE_RELEASE"
		optimize "On"
		buildoptions "/MD /EHsc"

	--reset filter 
	filter { }