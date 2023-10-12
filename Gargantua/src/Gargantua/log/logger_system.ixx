/*
* gargantua/log/logger_system.ixx
* 
* PURPOSE: global access to the game engine logger (used only for local debug).
*/

export module gargantua.log.logger_system;

import gargantua.types;
import gargantua.log.logger;
import gargantua.log.console_stream;


namespace gargantua::log
{
	export
	class LoggerSystem
	{
	public:
		static auto GetEngineLogger() -> Logger<ConsoleStream>&
		{
			static Logger<ConsoleStream> logger;
			return logger;
		}
	};
} // namespace gargantua::log