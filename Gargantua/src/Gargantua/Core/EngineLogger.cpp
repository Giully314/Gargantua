/*
Gargantua/Core/EngineLogger.cpp
*/
#include "EngineLogger.hpp"

#include "Gargantua/Log/Level.hpp"


namespace Gargantua
{
	namespace Core
	{
		UniqueRes<Log::Logger<Streams::ConsoleStream>> EngineLogger::logger{nullptr};


		EngineLogger::EngineLogger()
		{
			Init();
		}

		void EngineLogger::Init()
		{
			if (logger == nullptr)
			{
				logger = CreateUniqueRes<Log::Logger<Streams::ConsoleStream>>();
				logger->SetLevel(Log::Level::debug);
				logger->SetLoggerName("Engine");

				GRG_CORE_INFO("Init Engine Logger");
			}
		}

	} //namespace Core
} //namespace Gargantua