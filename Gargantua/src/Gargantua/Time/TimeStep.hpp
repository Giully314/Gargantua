#pragma once

#include <chrono>

#include "Gargantua/Types.hpp"

namespace Gargantua
{
	namespace Time
	{
		class TimeStep
		{
		public:
			TimeStep(std::chrono::duration<double> time_step_) : time_step(time_step_)
			{

			}

			//TODO: operator +, -


			inline real64_t GetInMilliSec() const noexcept
			{
				return time_step.count() * 1000;
			}

			inline real64_t GetInSec() const noexcept
			{
				return time_step.count();
			}


		private:
			std::chrono::duration<double> time_step;
		};
	} //namespace Time
} //namespace Gargantua


