#pragma once
/*
Gargantua/Systems/ResourceSystem.hpp

PURPOSE: Resource load utility.


CLASSES:
	ResourceSystem: class with static method.


DESCRIPTION:
	This class acts like a resource loading system for files of various format and type,
	text, meshes and so on.


USAGE:
	std::string shader_src = ResourceSystem::ReadFile("shader.vert");
*/

#include <string>
#include <string_view>

namespace Gargantua
{
	namespace Systems
	{
		struct ResourceSystem
		{
			static std::string ReadFile(std::string_view file_path);
		};
	} //namespace Systems
} //namespace Gargantua