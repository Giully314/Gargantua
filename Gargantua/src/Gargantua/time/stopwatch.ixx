/*
gargantua/time/stopwatch.ixx

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

export module gargantua.time.stopwatch;

import <chrono>;

import gargantua.types;
import gargantua.time.time_step;


namespace gargantua::time
{

	export class Stopwatch
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
	}; //class Stopwatch


} //namespace gargantua::time


