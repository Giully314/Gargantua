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
		}

		virtual auto RunTest() -> void = 0;

	protected:
		logging::Logger<logging::ConsoleStream> logger;
	};

} // namespace gargantua::test