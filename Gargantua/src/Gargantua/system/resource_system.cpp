/*
gargantua/system/resource_system.cpp
*/

module gargantua.system.resource_system;

import <fstream>;
import <sstream>;

import gargantua.types;



namespace gargantua::system
{

	auto ResourceSystem::ReadFile(std::string_view file_path) -> std::string
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



	auto ResourceSystem::LoadSharedTexture2d(std::string_view file_path) -> SharedRes<render::Texture2d>
	{
		auto tx = CreateSharedRes<render::Texture2d>();
		tx->Create();
		tx->Load(file_path);

		return tx;
	}

} //namespace Gargantua