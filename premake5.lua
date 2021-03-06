workspace "Gargantua"
	architecture "x86_64"
	configurations {"Debug", "Release"}
	
	toolset	'msc'

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


include "Gargantua/vendor/glfw"
include "Gargantua/vendor/Glad"
include "Gargantua/vendor/imgui"
include "Gargantua/vendor/stb_image"
include "Gargantua"
include "GargantuaEditor"
include "Sandbox"
