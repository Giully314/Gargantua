project "GargantuaTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	systemversion "latest"


	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {"src/**.hpp", "src/**.ixx", "src/**.cpp"}

	--technically the c++20 version specify the modules so it is not necessary to specify

	--include dirs extern to project do not work. i don't know if is is a bug from visual studio or premake.
	includedirs 
	{
		"%{wks.location}/Gargantua/src",
		"%{wks.location}/Gargantua/vendor/imgui",
		"%{wks.location}/Gargantua/vendor/Glad/include",
	}

	links {"Gargantua"}


	filter "files:**.cpp"
		compileas "C++"

	filter "files:**.ixx"
		compileas "Module"


	filter "configurations:Debug"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		optimize "On"
		runtime "Release"
		--buildoptions "/MT"