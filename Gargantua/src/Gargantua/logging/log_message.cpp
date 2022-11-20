/*
gargantua/logging/log_message.cpp
*/

module gargantua.logging.log;

import <unordered_map>;
import <string>;

namespace gargantua::logging
{
	std::unordered_map<Level, std::string> LogMessage::level_to_string = {
				{Level::debug,   "[DEBUG]"},
				{Level::info,	 "[INFO]"},
				{Level::warning, "[WARNING]"},
				{Level::error,	 "[ERROR]"},
				{Level::off,	 "[OFF]"},
	};
} //namespace gargantua::logging