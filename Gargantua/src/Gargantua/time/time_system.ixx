/*
* gargantua/time/time_system.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* TODO:
*	- temporary class, this system should be more advanced with customization of time.
*/

export module gargantua.time.time_system;

import gargantua.time.stopwatch;
import gargantua.time.time_step;

namespace gargantua::time
{
	export
	class TimeSystem
	{
	public:
		auto Startup() -> void
		{
			stopwatch.Tick();
		}


		auto Tick() -> TimeStep
		{
			return stopwatch.Tick();
		}
		

	private:
		Stopwatch stopwatch;
	};
} // namespace gargantua::time
