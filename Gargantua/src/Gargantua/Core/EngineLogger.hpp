#pragma once
/*
Gargantua/Core/EngineLogger.hpp

PURPOSE: Log information.

CLASSES:
	EngineLogger: Logger used by the Engine.

DESCRIPTION:
	Singleton class logger for the Engine part.

USAGE:
	GRG_CORE_ERROR("Error inside {}, message: {}", func_name, error_msg);

TODO:
	Move into Systems and make a LoggingSystem?
	How to avoid application side access this class? Is important?
*/


/*
Why i define this macro here instaed of inside premake file? 
Visual studio doesn't recognize macro definition inside the properties.
This is a known thing but who cares to fix it when you can waste people's time.
https://developercommunity.visualstudio.com/t/vs2019-does-not-appear-to-see-the-preprocessor-def/1337568
*/
#define GRG_LOGGER_ON

#include "Gargantua/Types.hpp"
#include "Gargantua/Log/Logger.hpp"
#include "Gargantua/Streams/ConsoleStream.hpp"

namespace Gargantua
{
	namespace Core
	{
		class EngineLogger
		{
		public:
			EngineLogger();
			~EngineLogger() = default;

			static UniqueRes<Log::Logger<Streams::ConsoleStream>>& Get() { return logger; }

		private:
			static UniqueRes<Log::Logger<Streams::ConsoleStream>> logger;
			void Init();
		};
	} //namespace Core
} //namespace Gargantua

#ifdef GRG_LOGGER_ON
#define GRG_CORE_DEBUG(...)				::Gargantua::Core::EngineLogger::Get()->Debug(__VA_ARGS__)
#define GRG_CORE_INFO(...)				::Gargantua::Core::EngineLogger::Get()->Info(__VA_ARGS__)
#define GRG_CORE_WARNING(...)			::Gargantua::Core::EngineLogger::Get()->Warning(__VA_ARGS__)
#define GRG_CORE_ERROR(...)				::Gargantua::Core::EngineLogger::Get()->Error(__VA_ARGS__)
#define GRG_CORE_LOGGER_FILTER(x)		::Gargantua::Core::EngineLogger::Get()->SetLevel(x)

#else
#define GRG_CORE_DEBUG(...)		
#define GRG_CORE_INFO(...)		
#define GRG_CORE_WARNING(...)	
#define GRG_CORE_ERROR(...)		
#define GRG_CORE_LOGGER_FILTER(x)
#endif