/*
gargantua/logging/logger.ixx

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

export module gargantua.logging.log:logger;

import <string>;
import <source_location>;
import <string_view>;
import <utility>;
import <format>;

import :level;
import :stream_concepts;
import :log_message;

namespace gargantua::logging
{
	export template <OutputStream<std::string_view> StreamType>
	class Logger
	{
	public:
		Logger() : level(Level::info), stream(), logger_name("Base")
		{

		}


		auto Flush() -> void
		{
			stream.Flush();
		}


		auto SetLoggerName(std::string name) -> void
		{
			logger_name = std::move(name);
		}

		auto GetLoggerName() const noexcept -> std::string_view
		{
			return logger_name;
		}


		auto SetLevel(Level level) -> void
		{
			this->level = level;
		}

		auto GetLevel() const noexcept -> Level
		{
			return level;
		}


		template <typename ...Args>
		auto Log(std::source_location loc, Level level, std::string_view msg, Args&& ...args) const -> void
		{
			if (ShouldLog(level))
			{
				std::string formatted_string = std::vformat(msg, std::make_format_args(args...));

				LogMessage lm{ logger_name, loc, level, formatted_string };
				stream << lm;
			}
		}


		template <typename ...Args>
		auto Log(Level level, std::string_view msg, Args&& ...args) const -> void
		{
			Log(std::source_location{}, level, msg, std::forward<Args>(args)...);
		}


		template <typename ...Args>
		auto Debug(std::string_view msg, Args&& ...args) const -> void
		{
			Log(std::source_location{}, Level::debug, msg, std::forward<Args>(args)...);
		}

		template <typename ...Args>
		auto Info(std::string_view msg, Args&& ...args) const -> void
		{
			Log(std::source_location{}, Level::info, msg, std::forward<Args>(args)...);
		}

		template <typename ...Args>
		auto Warning(std::string_view msg, Args&& ...args) const -> void
		{
			Log(std::source_location{}, Level::warning, msg, std::forward<Args>(args)...);
		}


		template <typename ...Args>
		auto Error(std::string_view msg, Args&& ...args) const -> void
		{
			Log(std::source_location{}, Level::error, msg, std::forward<Args>(args)...);
		}


	private:
		auto ShouldLog(Level l) const noexcept -> bool
		{
			return l >= level;
		}


		Level level;
		mutable StreamType stream;
		std::string logger_name;
	}; //class Logger
} //namespace gargantua::logging