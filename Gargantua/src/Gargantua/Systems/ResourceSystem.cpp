/*
Gargantua/Systems/ResourceSystem.cpp
*/
#include "ResourceSystem.hpp"

#include "Gargantua/Core/EngineLogger.hpp"

#include <string>
#include <string_view>
#include <fstream>
#include <sstream>

namespace Gargantua
{
	namespace Systems
	{
		std::string ResourceSystem::ReadFile(std::string_view file_path)
		{
			std::ifstream in{ file_path.data() };
			if (in.good())
			{
				std::stringstream buffer;
				buffer << in.rdbuf();
				return buffer.str();
			}
			return {};
		}
	} //namespace Systems
} //namespace Gargantua