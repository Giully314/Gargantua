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

		EngineLogger::~EngineLogger()
		{
			Shutdown();
		}

		void EngineLogger::Init()
		{
			if (logger == nullptr)
			{
				logger = CreateUniqueRes<Log::Logger<Streams::ConsoleStream>>();
				logger->SetLevel(Log::Level::debug);
				logger->SetLoggerName("Engine");

				GRG_CORE_DEBUG("Init Engine Logger");
			}
		}


		void EngineLogger::Shutdown()
		{
			GRG_CORE_DEBUG("Shutdown Engine Logger");
		}
	} //namespace Core
} //namespace Gargantua