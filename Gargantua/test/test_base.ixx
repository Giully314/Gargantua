export module gargantua.test.test_base;

import gargantua.logging.log;

export namespace gargantua::test
{
	
	class TestBase
	{
	public:
		TestBase()
		{
			logger.SetLevel(logging::Level::debug);
			logger.SetLoggerName("TestBaseLogger");

			logger.Debug("Creation of test class");

			mutex_logger.SetLevel(logging::Level::debug);
			mutex_logger.SetLoggerName("TestBaseMutexLog");
		}

		virtual auto RunTest() -> void = 0;

	protected:
		logging::Logger<logging::ConsoleStream> logger;
		logging::Logger<logging::MutexConsoleStream> mutex_logger;
	};

} // namespace gargantua::test