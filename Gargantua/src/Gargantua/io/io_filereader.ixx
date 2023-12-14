/*
* gargantua/io/io_filereader.ixx
* 
* PURPOSE: Provide file reading functionalities.
* 
* CLASSES:
*	FileReader: struct with static functions for reading files.
* 
*/

module;

#include <gargantua/log/logger_macro.hpp>

export module gargantua.io.file_reader;

import <string>;
import <fstream>;
import <sstream>;
import <filesystem>;
import <expected>;

import gargantua.log.logger_system;
import gargantua.io.errors;

namespace gargantua::io
{
	export struct FileReader
	{	
		static auto ReadFile(std::filesystem::path path) -> std::expected<std::string, FileError>
		{
			std::ifstream file{ path };
			if (!file)
			{
				GRG_CORE_ERROR("File {} not found.", path.string());
				return std::unexpected(FileError::FileNotFound);
			}
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}
	};
} // namespace gargantua::io
