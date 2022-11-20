export module gargantua.test.logging.test_logging;

import gargantua.logging.log;
import <string_view>;
import <memory>;


export namespace gargantua::test
{
	class TestLogging
	{
	public:
		TestLogging()
		{
			logger = std::make_unique< logging::Logger<logging::ConsoleStream>>();
		}
		
		auto RunTest() -> void;


	private:
		std::unique_ptr<logging::Logger<logging::ConsoleStream>> logger;
	};


	auto LogInformation(const std::unique_ptr<logging::Logger<logging::ConsoleStream>>& logger) -> void
	{
		logger->Info("It works even with const ptr");
		logger->SetLevel(logging::Level::debug);
	}

} //namespace gargantua::test