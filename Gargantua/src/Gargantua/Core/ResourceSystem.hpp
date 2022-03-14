#pragma once
/*
Gargantua/Core/ResourceSystem.hpp

PURPOSE: Resource load utility.


CLASSES:
	ResourceSystem: class with static method.


DESCRIPTION:
	This class acts like a resource loading system for files of various format and type,
	text, meshes and so on.


USAGE:

*/

#include <string>
#include <string_view>

namespace Gargantua
{
	namespace Core
	{
		struct ResourceSystem
		{
			static std::string ReadFile(std::string_view file_path);
		};
	} //namespace Core
} //namespace Gargantua