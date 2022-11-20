project "stb_image"
	kind "StaticLib"
	language "C"
	--staticruntime "On"
	systemversion "latest"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {"stb_image/**.h", "stb_image/**.c"}

	includedirs 
	{
		".",
	}


	filter "configurations:Debug"
		symbols "on"

	filter "configurations:Release"
		optimize "On"