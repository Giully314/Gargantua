/*
* gargantua/resource/file_reader.ixx
* 
* TODO: temporary name and structure.
*/

module;

#include <gargantua/log/logger_macro.hpp>

export module gargantua.resource.file_reader;

import <string>;
import <fstream>;
import <sstream>;

import gargantua.log.logger_system;

namespace gargantua::resource
{
	export 
	struct FileReader
	{
		static auto ReadFile(std::string_view filename) -> std::string
		{
			std::ifstream file{ filename.data() };
			if (!file)
			{
				GRG_CORE_ERROR("{} not found.", filename);
				return "";
			}
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}
	};

} // namespace gargantua::resource
