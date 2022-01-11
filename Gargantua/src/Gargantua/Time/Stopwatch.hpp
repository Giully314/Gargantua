#pragma once

#include <chrono>

#include "Gargantua/Time/TimeStep.hpp"

namespace Gargantua
{
	namespace Time
	{
		/*
		Measure the elapsed time between 2 calls of Tick.
		*/
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


