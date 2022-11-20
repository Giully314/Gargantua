/*
gargantua/time/time_step.ixx

PURPOSE: Keep track of the time between 2 ticks.


CLASSES:
	TimeStep: Value in second or millisecond of time passed between 2 ticks.


DESCRIPTION:


USAGE:
	Stopwatch s;

	TimeStep ts = s.Tick();

	if (ts.GetInSec() < some_time)
	{

	}
*/

export module gargantua.time.time_step;

import <chrono>;
import <compare>;

import gargantua.types;


export namespace gargantua::time
{
	class TimeStep
	{
	public:
		TimeStep() = default;

		TimeStep(std::chrono::duration<double> time_step_) : time_step(time_step_)
		{

		}

		TimeStep(real64_t time_step_) : time_step(time_step_)
		{

		}


		auto operator<=>(const TimeStep& ts) const = default;


		auto operator-=(const TimeStep& ts) -> TimeStep&
		{
			time_step -= ts.time_step;
			return *this;
		}

		auto operator+=(const TimeStep& ts) -> TimeStep&
		{
			time_step += ts.time_step;
			return *this;
		}


		auto GetInMilliSec() const noexcept -> real64_t
		{
			return time_step.count() * 1000;
		}

		auto GetInSec() const noexcept -> real64_t
		{
			return time_step.count();
		}


	private:
		std::chrono::duration<double> time_step{ 0 };
	}; //class TimeStep


	//*************************** FRIEND OPERATORS ************************************

	inline auto operator-(TimeStep ts1, const TimeStep& ts2) -> TimeStep
	{
		ts1 -= ts2;
		return ts1;
	}


	inline auto operator+(TimeStep ts1, const TimeStep& ts2) -> TimeStep
	{
		ts1 += ts2;
		return ts1;
	}


} //namespace gargantua::time


