project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	systemversion "latest"
	-- compileas "Module"


	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {"src/**.ixx", "src/**.cpp"}


	includedirs 
	{
		"%{wks.location}/Gargantua/src",
		"%{wks.location}/Gargantua/test",
		"%{wks.location}/Gargantua/vendor/imgui",
		"%{wks.location}/Gargantua/vendor/Glad/include",
		"%{wks.location}/GargantuaEditor/src",
	}

	links {"Gargantua"}


	--filter "files:**.cpp"
		--compileas "C++"

	--filter "files:**.ixx"
		--compileas "Module"

	filter "configurations:Debug"
		symbols "On"
		runtime "Debug"
		buildoptions "/MDd /EHsc"

	filter "configurations:Release"
		optimize "On"
		runtime "Release"
		buildoptions "/MD /EHsc"

	filter { }