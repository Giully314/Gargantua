/*
gargantua/logging/log_message.ixx

PURPOSE: Message information.

CLASSES:
	LogMessage: Class that contatins the message and output it to a stream.

DESCRIPTION:
	This class is a wrapper for a string that represents a message, adding other informations like time,
	thread, ecc.

USAGE:


TODO: fix time, add thread id.

*/

export module gargantua.logging.log:log_message;

import <string_view>;
import <source_location>;
import <string>;
import <unordered_map>;

import :level;
import :stream_concepts;

namespace gargantua::logging
{
	export 
	class LogMessage
	{
	public:
		LogMessage(std::string_view logger_name_, std::source_location location_, Level level_,
			std::string_view msg_) :
			logger_name(logger_name_), location(std::move(location_)), level(level_), msg(msg_)
		{

		}

		template <OutputStream<std::string> Stream>
		friend auto operator<<(Stream& s, LogMessage lm) -> Stream&
		{
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
		std::string logger_name;
		std::source_location location;
		Level level;
		std::string_view msg;
		//const std::time_t time;
		//thread_id

		static std::unordered_map<Level, std::string> level_to_string;
	}; //class LogMessage

} //namespace gargantua::logging