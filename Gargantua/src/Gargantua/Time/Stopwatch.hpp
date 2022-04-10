#pragma once
/*
Gargantua/Time/Stopwatch.hpp

PURPOSE: Get the time between 2 moments.

CLASSES:
	Stopwatch: Measure time.

DESCRIPTION:
	Measure the elapsed time between 2 calls of Tick.

USAGE:

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
			inline TimeStep Tick()
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


