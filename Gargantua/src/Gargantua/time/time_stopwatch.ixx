/*
* gargantua/time/time_stopwatch.ixx
* 
* PURPOSE: Measure time.
* 
* CLASSES:
* 	Stopwatch: Get the time between 2 ticks.
* 
* DESCRIPTION:
*	The class Stopwatch is used to keep track of the elapsed time between 2 calls of Tick(). 
* 
* USAGE:
* 	Stopwatch s;
*	
*	// Time elapsed between the construction of Stopwatch and Tick().
* 	TimeStep ts1 = s.Tick();
* 
* 	...
*	
*	// Time elapsed between the previous call of Tick().
* 	TimeStep ts2 = s.Tick();
*/

export module gargantua.time.stopwatch;

import <chrono>;

import gargantua.types;
import gargantua.time.time_step;


namespace gargantua::time
{
	export class Stopwatch
	{
	public:
		constexpr explicit Stopwatch() = default;

		auto Tick() -> TimeStep
		{
			auto temp = std::chrono::steady_clock::now();
			TimeStep ts{ std::chrono::duration<f64>(temp - s) };
			s = temp;

			return ts;
		}

	private:
		std::chrono::time_point<std::chrono::steady_clock> s{ std::chrono::steady_clock::now() };
	}; 
} //namespace gargantua::time


