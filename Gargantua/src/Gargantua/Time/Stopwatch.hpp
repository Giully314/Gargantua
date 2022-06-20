#pragma once
/*
Gargantua/Time/Stopwatch.hpp

PURPOSE: Measure time.


CLASSES:
	Stopwatch: Get the time between 2 ticks.


DESCRIPTION:
	Measure the elapsed time between 2 calls of Tick.


USAGE:
	Stopwatch s;

	TimeStep ts1 = s.Tick();
	
	...
	
	TimeStep ts2 = s.Tick();
*/


#include "Gargantua/Time/TimeStep.hpp"

#include <chrono>


namespace Gargantua
{
	namespace Time
	{
		class Stopwatch
		{
		public:
			TimeStep Tick()
			{
				auto temp = std::chrono::steady_clock::now();
				TimeStep ts{ std::chrono::duration<real64_t>(temp - s) };
				s = temp;

				return ts;
			}

		private:
			std::chrono::time_point<std::chrono::steady_clock> s{ std::chrono::steady_clock::now() };
		};

	} //namespace Time
} //namespace Gargantua


