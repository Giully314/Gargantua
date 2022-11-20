/*
gargantua/system/time_system.ixx


PURPOSE: Control time in the engine.


CLASSES:
	TimeSystem: Customize the time in the game loop and get access to a unified time system across the engine.


DESCRIPTION:
	https://gafferongames.com/post/fix_your_timestep/


USAGE:
	TimeSystem time_sys;

	time_sys.SetUpdatePerSecond(60.0f);

	while (game_loop_is_true)
	{
		time_sys.ComputeFrameTime();
		const Systems::TimeInfo& info = time_sys.GetInfo();

		//Update the logic with a fixed time step.
		do
		{
			time_sys.Tick();
			engine_event_sys.ProcessEvents();
			app_event_sys.ProcessEvents();
			app->Execute(info.ts);
		} while (info.valid);
	}

TODO:
	add the possibility to register different stopwatch or time elapsed and get noticed with an event?
	change from double to integer representation.
*/

export module gargantua.system.time_system;

import gargantua.types;

import gargantua.time.time;


export namespace gargantua::system
{

	struct TimeInfo
	{
		bool valid = false;
		time::TimeStep ts;
	}; //struct TimeInfo


	class TimeSystem
	{
	public:
		auto SetUpdatePerSecond(real64_t update_per_second) noexcept -> void
		{
			this->update_per_second = update_per_second;
			info.ts = time::TimeStep{ 1.0 / update_per_second };
		}


		//Time between 2 rendered frames.
		auto ComputeFrameTime() -> void;

		auto Tick() -> void;


		auto GetInfo() const noexcept -> const TimeInfo&
		{
			return info;
		}


	private:
		time::Stopwatch stopwatch;

		real64_t update_per_second = 60.0;

		time::TimeStep current_time;
		time::TimeStep current_frame_time;
		time::TimeStep accumulator;

		TimeInfo info;
	}; //class TimeSystem

} //namespace gargantua::system