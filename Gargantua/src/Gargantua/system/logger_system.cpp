/*
gargantua/system/logger_system.cpp
*/

module gargantua.system.logger_system;


namespace gargantua::system
{
	UniqueRes<logging::Logger<logging::ConsoleStream>> LoggerSystem::console_logger{ nullptr };
	UniqueRes<logging::Logger<logging::MutexConsoleStream>> mutex_console_logger{ nullptr };

	LoggerSystem::LoggerSystem()
	{
		InitConsoleLogger();
		InitMutexConsoleLogger();
	}

	auto LoggerSystem::InitConsoleLogger() -> void 
	{
		console_logger = CreateUniqueRes<logging::Logger<logging::ConsoleStream>>();
		console_logger->SetLevel(logging::Level::debug);
		console_logger->SetLoggerName("Console");
	}

	auto LoggerSystem::InitMutexConsoleLogger() -> void
	{
		mutex_console_logger = CreateUniqueRes<logging::Logger<logging::MutexConsoleStream>>();
		mutex_console_logger->SetLevel(logging::Level::debug);
		mutex_console_logger->SetLoggerName("MutexConsole");
	}

} //namespace gargantua::system