#pragma once
/*
Gargantua/Time/TimeStep.hpp

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


#include "Gargantua/Types.hpp"


#include <chrono>
#include <compare>

namespace Gargantua
{
	namespace Time
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
			

			friend TimeStep operator-(TimeStep ts1, const TimeStep& ts2);
			friend TimeStep operator+(TimeStep ts1, const TimeStep& ts2);


			TimeStep& operator-=(const TimeStep& ts)
			{
				time_step -= ts.time_step;
				return *this;
			}

			TimeStep& operator+=(const TimeStep& ts)
			{
				time_step += ts.time_step;
				return *this;
			}


			real64_t GetInMilliSec() const noexcept
			{
				return time_step.count() * 1000;
			}

			real64_t GetInSec() const noexcept
			{
				return time_step.count();
			}


		private:
			std::chrono::duration<double> time_step{0};
		};


		//*************************** FRIEND OPERATORS ************************************

		inline TimeStep operator-(TimeStep ts1, const TimeStep& ts2)
		{
			ts1 -= ts2;
			return ts1;
		}


		inline TimeStep operator+(TimeStep ts1, const TimeStep& ts2)
		{
			ts1 += ts2;
			return ts1;
		}

	} //namespace Time
} //namespace Gargantua


