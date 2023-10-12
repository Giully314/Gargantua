workspace "Gargantua"
	architecture "x86_64"
	configurations {"Debug", "Release"}
	
	toolset	'msc'

	startproject "GargantuaEditor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "STLHeaderUnit"
include "Gargantua/vendor/glfw"
include "Gargantua/vendor/Glad"
include "Gargantua/vendor/imgui"
include "Gargantua/vendor/stb_image"
include "Gargantua"
include "GargantuaEditor"
include "Sandbox"