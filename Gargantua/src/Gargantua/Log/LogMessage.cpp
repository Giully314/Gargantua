#include "LogMessage.hpp"

namespace Gargantua
{
	namespace Log
	{
		std::unordered_map<Level, std::string> LogMessage::level_to_string = {
				{Level::debug,   "[DEBUG]"},
				{Level::info,	 "[INFO]"},
				{Level::warning, "[WARNING]"},
				{Level::error,	 "[ERROR]"},
				{Level::off,	 "[OFF]"},
		};
	} //namespace Log
} //namespace Gargantua