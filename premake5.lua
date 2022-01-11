workspace "Gargantua"
	architecture "x86_64"
	configurations {"Debug", "Release"}
	
	toolset	'msc'
	staticruntime 'On'

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


include "Gargantua/vendor/glfw"
include "Gargantua"
include "Sandbox"
