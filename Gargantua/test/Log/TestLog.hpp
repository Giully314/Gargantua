#pragma once

#include "Gargantua/Log/Level.hpp"
#include "Gargantua/Log/Logger.hpp"
#include "Gargantua/Streams/ConsoleStream.hpp"


namespace Gargantua
{
	namespace Test
	{
		void TestLog()
		{
			Log::Logger<Streams::ConsoleStream> logger;
			logger.SetLoggerName("Engine");
			logger.SetLevel(Log::Level::debug);
			logger.Debug("signori eccoci qui {}", 10);
		}

	}
}