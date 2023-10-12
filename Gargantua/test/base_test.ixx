/*
* gargantua/test/base_test.ixx
*/

export module gargantua.test.base_test;

import gargantua;

namespace gargantua::test
{
	export 
	class BaseTest
	{
	public:
		BaseTest()
		{
			logger.SetLevel(log::Level::debug);
			logger.SetLoggerName("TestBaseLogger");

			logger.Debug("Creation of test class");

			mutex_logger.SetLevel(log::Level::debug);
			mutex_logger.SetLoggerName("TestBaseMutexLog");
		}

		virtual auto RunTest() -> void = 0;

	protected:
		log::Logger<log::ConsoleStream> logger;
		log::Logger<log::MutexConsoleStream> mutex_logger;
	};
} // namespace gargantua::test
