#pragma once

#include "Gargantua/Log/Level.hpp"
#include "Gargantua/Concepts/Stream.hpp"

#include <unordered_map>
#include <source_location>
#include <string>


namespace Gargantua
{
	namespace Log
	{
		/*
		This class is a wrapper for a string that represents a message, adding other informations like time,
		thread, ecc.

		TODO: fix time, add thread id.
		*/
		class LogMessage
		{
		public:
			LogMessage(std::string_view logger_name_, std::source_location location_, Level level_, 
				std::string_view msg_) :
				logger_name(logger_name_), location(std::move(location_)), level(level_), msg(msg_)
			{

			}

			template <Concepts::OutputStream<std::string> Stream>
			friend Stream& operator<<(Stream& s, LogMessage lm)
			{
				//FOR NOW NO TIME BECAUSE C++ TIME SYSTEM SUCKS.

				/*std::string out;
				out.reserve(lm.level_to_string[lm.level].size() + lm.msg.size() + 3);
				out += lm.level_to_string[lm.level];
				out += " ";
				out += lm.msg;
				out += "\n";
				s << out; */

				s << lm.level_to_string[lm.level] << lm.logger_name
					<< lm.location.file_name() << " "
					<< lm.location.function_name() << " : "
					<< lm.msg << "\n";

				return s;
			}


		private:
			std::string_view logger_name;
			std::source_location location;
			Level level;
			std::string_view msg;
			//const std::time_t time;
			//thread_id

			static std::unordered_map<Level, std::string> level_to_string;
		};
	} //namespace Log
} //namespace Gargantua