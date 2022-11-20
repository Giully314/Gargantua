/*
gargantua/system/time_system.cpp
*/

module gargantua.system.time_system;



namespace gargantua::system
{

	auto TimeSystem::ComputeFrameTime() -> void
	{
		time::TimeStep new_time = stopwatch.Tick();
		current_frame_time = new_time - current_time;
		current_time = new_time;

		accumulator += current_frame_time;
	}


	auto TimeSystem::Tick() -> void
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

} //namespace gargantua::system