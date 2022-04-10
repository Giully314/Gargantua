#pragma once
/*
Gargantua/Log/Logger.hpp

PURPOSE: Logger class.

CLASSES:
	Logger: Log message using a stream.

DESCRIPTION:
	A Logger is a class that allows to register messages and send them to the chosen stream.
	Messages are formatted using std::format.

USAGE:
	Logger<CoonsoleStream> console_logger;
	console_logger.Debug("debug message {}", code);
*/

#include "Gargantua/Concepts/Stream.hpp"
#include "Gargantua/Log/Level.hpp"
#include "Gargantua/Log/LogMessage.hpp"


#include <iostream>
#include <string>
#include <format>
#include <source_location>


namespace Gargantua
{
	namespace Log
	{
		template <Concepts::OutputStream<std::string_view> StreamType>
		class Logger
		{
		public:
			Logger() : level(Level::info), stream(), logger_name("Base")
			{

			}


			void Flush()
			{
				stream.Flush();
			}
			

			inline void SetLoggerName(std::string name)
			{
				logger_name = std::move(name);
			}

			inline std::string_view GetLoggerName() const noexcept
			{
				return logger_name;
			}


			inline void SetLevel(Level level)
			{
				this->level = level;
			}

			inline Level GetLevel() const noexcept
			{
				return level;
			}


			template <typename ...Args>
			void Log(std::source_location loc, Level level, std::string_view msg, Args&& ...args)
			{
				if (ShouldLog(level))
				{
					std::string formatted_string = std::vformat(msg, std::make_format_args(args...));

					LogMessage lm{ logger_name, loc, level, formatted_string };
					stream << lm;
				}
			}


			template <typename ...Args>
			void Log(Level level, std::string_view msg, Args&& ...args)
			{
				Log(std::source_location{}, level, msg, std::forward<Args>(args)...);
			}


			template <typename ...Args>
			void Debug(std::string_view msg, Args&& ...args)
			{
				Log(std::source_location{}, Level::debug, msg, std::forward<Args>(args)...);
			}

			template <typename ...Args>
			void Info(std::string_view msg, Args&& ...args)
			{
				Log(std::source_location{}, Level::info, msg, std::forward<Args>(args)...);
			}

			template <typename ...Args>
			void Warning(std::string_view msg, Args&& ...args)
			{
				Log(std::source_location{}, Level::warning, msg, std::forward<Args>(args)...);
			}


			template <typename ...Args>
			void Error(std::string_view msg, Args&& ...args)
			{
				Log(std::source_location{}, Level::error, msg, std::forward<Args>(args)...);
			}


		private:
			inline bool ShouldLog(Level l) const noexcept
			{
				return l >= level;
			}


			Level level;
			StreamType stream;
			std::string logger_name;
		};

	} //namespace Log
} //namespace Gargantua