workspace "Gargantua"
	architecture "x86_64"
	configurations {"Debug", "Release"}
	
	toolset	'MSC'
	staticruntime 'On'

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


include "Gargantua"
include "Sandbox"
