#pragma once
/*
Gargantua/Systems/TimeSystem.hpp


PURPOSE: Control time in the engine.


CLASSES:
	TimeSystem: Customize the time in the game loop and get access to a unified time system across the engine.


DESCRIPTION:
	https://gafferongames.com/post/fix_your_timestep/


USAGE: 


TODO: 
	add the possibility to register different stopwatch or time elapsed and get noticed with an event?
	change from double to integer representation.	
*/


#include "Gargantua/Time/TimeStep.hpp"
#include "Gargantua/Time/Stopwatch.hpp"


namespace Gargantua
{
	namespace Systems
	{
		struct TimeInfo
		{
			bool valid = false;
			Time::TimeStep ts;
		};


		class TimeSystem
		{
		public:
			void SetUpdatePerSecond(real64_t update_per_second) noexcept
			{
				this->update_per_second = update_per_second;
				info.ts = Time::TimeStep{ 1.0 / update_per_second };
			}
			

			//Time between 2 frames (render)
			void ComputeFrameTime();

			void Tick();


			const TimeInfo& GetInfo() const noexcept
			{
				return info;
			}



		private:
			Time::Stopwatch stopwatch;
			
			real64_t update_per_second = 60.0;

			Time::TimeStep current_time;
			Time::TimeStep current_frame_time;
			Time::TimeStep accumulator;

			TimeInfo info;

		};
	} //namespace Systems
} //namespace Gargantua