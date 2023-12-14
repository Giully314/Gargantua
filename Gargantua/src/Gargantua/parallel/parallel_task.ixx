/*
* gargantua/parallel/parallel_task.ixx
* 
* PURPOSE: Provide a wrapper for functions to be executed by the thread pool.
* 
* CLASSES:
*	Task: wrapper for a callable with signature void().
* 
*/

export module gargantua.parallel.task;

import <concepts>;
import <type_traits>;
import <functional>;

import gargantua.types;


namespace gargantua::parallel
{
	export class Task : NonCopyable
	{
	public:
		template <typename F>
			requires std::invocable<F> && std::is_void_v<std::invoke_result_t<F>>
		Task(F&& f) : t(std::forward<F>(f))
		{

		}


		auto operator()() -> void
		{
			t();
		}


	private:
		std::function<void()> t;
	};

} // namespace gargantua::parallel