project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "On"
	systemversion "latest"


	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {"src/**.hpp", "src/**.cpp"}

	includedirs 
	{
		"%{wks.location}/Gargantua/src",
		"%{wks.location}/Gargantua/test",
		"%{wks.location}/Gargantua/vendor/imgui",
		"%{wks.location}/Gargantua/vendor/Glad/include",
	}

	links {"Gargantua"}


	filter "configurations:Debug"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		optimize "On"
		runtime "Release"
		--buildoptions "/MT"