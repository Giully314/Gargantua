#pragma once

#include "Gargantua/Parallel/Task.hpp"

#include <concepts>
#include <tuple>

namespace Gargantua
{
	namespace Parallel
	{
		/*
		Wrapper for lambda class.
		*/
		template <typename F, typename ...Args>
		requires std::movable<F> && std::invocable<F, Args...>
		class LambdaTask final : public Task
		{
		public:
			LambdaTask(F&& lambda, Args&& ...params) : f(std::move(lambda)), args(std::make_tuple<Args...>(std::forward<Args>(params)...))
			{

			}

			inline void Execute()
			{
				f(std::get<Args>(args)...);
			}

		private:
			F f;
			std::tuple<Args...> args;
		};
	} //namespace Parallel 
} //namespace Gargantua

