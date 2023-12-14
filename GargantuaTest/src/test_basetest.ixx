/*
* gargantua/test/base_test.ixx
*/

export module gargantuatest.testbase;

import <string>;
import <string_view>;

import gargantua;

using namespace gargantua;
using namespace gargantua::log;

namespace gargantuatest
{
	export
	template <typename Stream>
	class TesterLogger
	{
	public:
		explicit TesterLogger(std::string_view name_, non_owned_res<Logger<Stream>> l) :
			name(name_), logger(l)
		{
			logger->Debug("Start {}", name);
		}


		~TesterLogger()
		{
			logger->Debug("PASSED {}\n\n", name);
		}

	private:
		std::string name;
		non_owned_res<Logger<Stream>> logger;
	};


	export class TestBase
	{
	public:
		TestBase()
		{
			logger.SetLevel(Level::debug);
			logger.SetLoggerName("TestBaseLogger");

			logger.Debug("Creation of test class");

			mutex_logger.SetLevel(Level::debug);
			mutex_logger.SetLoggerName("TestBaseMutexLog");
		}


		auto ConsoleLogTester(std::string_view name) -> TesterLogger<ConsoleStream>
		{
			return TesterLogger{ name, &logger };
		}
		
		auto MutexConsoleLogTester(std::string_view name) -> TesterLogger<MutexConsoleStream>
		{
			return TesterLogger{ name, &mutex_logger };
		}

	protected:
		//using namespace gargantua;
		Logger<ConsoleStream> logger;
		Logger<MutexConsoleStream> mutex_logger;
	};



} // namespace gargantua::test
