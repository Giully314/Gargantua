/*
* gargantua/parallel/task_system.ixx
* 
* PURPOSE: implementation of a thread pool.
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* TODO:
*	- work stealing.
*	- run/stop threads while saving the tasks to be executed.
*/


export module gargantua.parallel.task_system;

import <thread>;
import <stop_token>;
import <atomic>;
import <queue>;
import <future>;
import <type_traits>;
import <utility>;
import <vector>;
import <concepts>;

import gargantua.types;
import gargantua.ds.concurrent_queue;
import gargantua.parallel.task;

namespace gargantua::parallel
{
	export
	class TaskSystem : private NonCopyable, NonMovable
	{
	public:
		static
		auto Instance() -> TaskSystem&
		{
			static TaskSystem ts;
			return ts;
		}

		~TaskSystem();

		/*
		* Register a task to be executed and returns a future that can be used as sync
		* to wait for the task to finish.
		*/
		template <typename F>
			requires std::invocable<F>
		[[nodiscard]]
		auto RegisterWait(F f) -> std::future<std::invoke_result_t<F>>
		{
			using result_type = std::invoke_result_t<F>;
			std::packaged_task<result_type()> task(f);
			std::future<result_type> res(task.get_future());

			if (local_tasks_queue)
			{
				local_tasks_queue->emplace(std::move(task));
			}
			else
			{
				pool_tasks_queue.push(std::move(task));
			}
			return res;
		}


		/*
		* Register a task to be executed.
		*/
		template <typename F>
			requires std::invocable<F>
		auto Register(F f) -> void
		{
			if (local_tasks_queue)
			{
				local_tasks_queue->emplace(std::move(f));
			}
			else
			{
				pool_tasks_queue.push(std::move(f));
			}
		}




	private:
		auto WorkerThread(std::stop_source stop_source) -> void;
		auto RunPendingTask() -> void;

		auto StopWorkers() -> void
		{
			stop_source.request_stop();
		}

	private:
		TaskSystem();

	private:
		using local_queue_type = std::queue<Task>;

		// NOTE: the order of definition does matters. The queues must be destroyed
		// after the workers.

		//std::atomic_bool finished;
		std::stop_source stop_source;
		ds::ConcurrentQueue<Task> pool_tasks_queue;
		inline static thread_local unique_res<local_queue_type> local_tasks_queue;
		
		std::vector<std::jthread> threads;
	};

} // namespace gargantua::parallel