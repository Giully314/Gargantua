/*
Gargantua/Systems/TimeSystem.cpp
*/
#include "Gargantua/Systems/TimeSystem.hpp"



namespace Gargantua
{
	namespace Systems
	{
		void TimeSystem::ComputeFrameTime()
		{
			Time::TimeStep new_time = stopwatch.Tick();
			current_frame_time = new_time - current_time;
			current_time = new_time;

			accumulator += current_frame_time;
		}


		void TimeSystem::Tick()
		{
			if (accumulator >= info.ts)
			{
				accumulator -= info.ts;
				info.valid = true;
			}
			else
			{
				info.valid = false;
			}
		}

	} //namespace Systems
} //namespace Gargantua