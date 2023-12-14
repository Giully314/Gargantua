/*
* gargantua/time/time_timestep.ixx
* 
* PURPOSE: Keep track of the elapsed time.
* 
* 
* CLASSES:
* 	TimeStep: Value in second or millisecond of elapsed time.
* 
* 
* USAGE:
* 	Stopwatch s;
* 
* 	TimeStep ts = s.Tick();
* 
* 	if (ts.GetInSec() < some_time)
* 	{
* 
* 	}
*/

export module gargantua.time.time_step;

import <chrono>;
import <compare>;

import gargantua.types;


namespace gargantua::time
{
	export class TimeStep
	{
	public:
		constexpr explicit TimeStep() = default;

		constexpr explicit TimeStep(std::chrono::duration<double> time_step_) : time_step(time_step_)
		{

		}

		constexpr explicit TimeStep(f64 time_step_) : time_step(time_step_)
		{

		}


		constexpr auto operator<=>(const TimeStep& ts) const = default;


		constexpr auto operator-=(const TimeStep& ts) noexcept -> TimeStep&
		{
			time_step -= ts.time_step;
			return *this;
		}

		constexpr auto operator+=(const TimeStep& ts) noexcept -> TimeStep&
		{
			time_step += ts.time_step;
			return *this;
		}


		constexpr auto Milliseconds() const noexcept -> f64
		{
			return time_step.count() * 1000;
		}

		constexpr auto Seconds() const noexcept -> f64
		{
			return time_step.count();
		}


	private:
		std::chrono::duration<double> time_step{ 0 };
	};


	//*************************** FRIEND OPERATORS ************************************

	inline constexpr auto operator-(TimeStep ts1, const TimeStep& ts2) noexcept -> TimeStep
	{
		ts1 -= ts2;
		return ts1;
	}


	inline constexpr auto operator+(TimeStep ts1, const TimeStep& ts2) noexcept -> TimeStep
	{
		ts1 += ts2;
		return ts1;
	}
} //namespace gargantua::time


