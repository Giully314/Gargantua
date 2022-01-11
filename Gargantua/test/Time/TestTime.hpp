#pragma once

#include "Gargantua/Time/Stopwatch.hpp"
#include "Gargantua/Time/TimeStep.hpp"

#include <iostream>

namespace Gargantua
{
	namespace Test
	{
		void TestTime()
		{
			Time::Stopwatch stopwatch;

			auto ts = stopwatch.Tick();
		
			std::cout << ts.GetInMilliSec() << std::endl;
			std::cout << ts.GetInSec() << std::endl;
		}
	}
}