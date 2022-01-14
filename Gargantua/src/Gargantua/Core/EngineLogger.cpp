#include "EngineLogger.hpp"
#include "Gargantua/Log/Level.hpp"


namespace Gargantua
{
	namespace Core
	{
		UniqueRes<Log::Logger<Streams::ConsoleStream>> EngineLogger::logger{nullptr};

		void EngineLogger::Start()
		{
			if (logger == nullptr)
			{
				logger = CreateUniqueRes<Log::Logger<Streams::ConsoleStream>>();
				logger->SetLevel(Log::Level::debug);
				logger->SetLoggerName("Engine");
			}
		}
	} //namespace Core
} //namespace Gargantua