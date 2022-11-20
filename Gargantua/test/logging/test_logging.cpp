module gargantua.test.logging.test_logging;

namespace gargantua::test
{
	auto TestLogging::RunTest() -> void
	{
		logger->SetLevel(logging::Level::info);

		logger->Info("This is a test {}", 1);

		LogInformation(logger);
	}

} //namespace gargantua::test