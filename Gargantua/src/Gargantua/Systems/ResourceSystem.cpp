/*
Gargantua/Systems/ResourceSystem.cpp
*/
#include "ResourceSystem.hpp"

#include "Gargantua/Types.hpp"

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



		SharedRes<Renderer::Texture2d> ResourceSystem::LoadSharedTexture2d(std::string_view file_path)
		{
			auto tx = CreateSharedRes<Renderer::Texture2d>();
			tx->Create();
			tx->Load(file_path);

			return tx;
		}
	} //namespace Systems
} //namespace Gargantua