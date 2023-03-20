/*
* gargantua/log/logger_system.ixx
* 
* PURPOSE:
* CLASSES:
* DESCRIPTION:
*/

export module gargantua.logging.logger_system;

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
			logger.SetLevel(Level::debug);
			return logger;
		}
	};
} // namespace gargantua::log