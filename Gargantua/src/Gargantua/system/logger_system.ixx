/*
gargantua/system/engine_logger.ixx

PURPOSE: Log information.

CLASSES:
	EngineLogger: Logger used by the Engine.

DESCRIPTION:
	Singleton class logger for the Engine part.

USAGE:
	GRG_CORE_ERROR("Error inside {}, message: {}", func_name, error_msg);

TODO:
	How to avoid application side access this class? Is important?
*/


export module gargantua.system.logger_system;

import gargantua.types;

import gargantua.logging.log;


namespace gargantua::system
{

	export class LoggerSystem
	{
	public:
		LoggerSystem();

		static auto Get() -> const UniqueRes<logging::Logger<logging::ConsoleStream>>&
		{ 
			return console_logger;
		} 

	private:
		static UniqueRes<logging::Logger<logging::ConsoleStream>> console_logger;
		static UniqueRes<logging::Logger<logging::MutexConsoleStream>> mutex_console_logger;

		auto InitConsoleLogger() -> void;
		auto InitMutexConsoleLogger() -> void;
	};
} //namespace gargantua::system

//#ifdef GRG_LOGGER_ON
//#define GRG_CORE_DEBUG(...)				::Gargantua::Core::EngineLogger::Get()->Debug(__VA_ARGS__)
//#define GRG_CORE_INFO(...)				::Gargantua::Core::EngineLogger::Get()->Info(__VA_ARGS__)
//#define GRG_CORE_WARNING(...)			::Gargantua::Core::EngineLogger::Get()->Warning(__VA_ARGS__)
//#define GRG_CORE_ERROR(...)				::Gargantua::Core::EngineLogger::Get()->Error(__VA_ARGS__)
//#define GRG_CORE_LOGGER_FILTER(x)		::Gargantua::Core::EngineLogger::Get()->SetLevel(x)
//
//#else
//#define GRG_CORE_DEBUG(...)		
//#define GRG_CORE_INFO(...)		
//#define GRG_CORE_WARNING(...)	
//#define GRG_CORE_ERROR(...)		
//#define GRG_CORE_LOGGER_FILTER(x)
//#endif