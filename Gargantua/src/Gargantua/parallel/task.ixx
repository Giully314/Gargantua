/*
* gargantua/parallel/task.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* 
*/

export module gargantua.parallel.task;

import <concepts>;
import <type_traits>;
import <functional>;

import gargantua.types;


namespace gargantua::parallel
{
	export
	class Task : private NonCopyable
	{
	public:
		Task() = default;

		template <typename F>
			requires std::invocable<F> && std::is_void_v<std::invoke_result_t<F>>
		Task(F&& f) : t(std::forward<F>(f))
		{

		}

		Task(Task&&) = default;
		Task& operator=(Task&&) = default;


		auto operator()() -> void
		{
			t();
		}


	private:
		std::function<void()> t;

		/*struct BaseTask
		{
			virtual auto Execute() -> void = 0;
			virtual ~BaseTask() = default;
		};

		template <typename F>
			requires std::invocable<F>
		struct TaskWrapper : public BaseTask
		{
			TaskWrapper(F&& f_) : f(std::forward<F>(f))
			{

			}

			auto Execute() -> void override
			{
				f();
			}

			F f;
		};

		unique_res<BaseTask> t;*/
	};

} // namespace gargantua::parallel