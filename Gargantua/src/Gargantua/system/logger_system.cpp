/*
gargantua/system/logger_system.cpp
*/

module gargantua.system.logger_system;


namespace gargantua::system
{

	UniqueRes<logging::Logger<logging::ConsoleStream>> LoggerSystem::logger{ nullptr };


	LoggerSystem::LoggerSystem()
	{
		Init();
	}

	void LoggerSystem::Init()
	{
		if (!logger)
		{
			logger = CreateUniqueRes<logging::Logger<logging::ConsoleStream>>();
			logger->SetLevel(logging::Level::debug);
			logger->SetLoggerName("Engine");
		}
	}

} //namespace gargantua::system