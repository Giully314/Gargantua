/*
gargantua/system/resource_system.ixx

PURPOSE: Resource load utility.


CLASSES:
	ResourceSystem: class with static method.


DESCRIPTION:
	This class acts like a resource loading system for files of various format and type,
	text, meshes and so on.


USAGE:
	std::string shader_src = ResourceSystem::ReadFile("shader.vert");
*/

export module gargantua.system.resource_system;

import <string>;
import <string_view>;

import gargantua.types;

import gargantua.render.texture2d;


namespace gargantua::system
{

	export struct ResourceSystem
	{
		static auto ReadFile(std::string_view file_path) -> std::string;

		static auto LoadSharedTexture2d(std::string_view file_path) ->SharedRes<render::Texture2d>;
	}; //struct ResourceSystem

} //namespace gargantua::system