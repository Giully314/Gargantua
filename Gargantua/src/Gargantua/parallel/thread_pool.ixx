/*
gargantua/parallel/thread_pool.ixx

PURPOSE: Implement a thread pool.

CLASSES:
	ThreadPool: Allows parallel task execution done by a pool of thread.


DESCRIPTION:
	The class is a basic implementation of a thread pool with a central mutex queue, handled by the class, and a nonmutex
	personal queue for each thread. 
	Each thread can get a task to execute by its queue or by the central queue; if there are no tasks the thread calls 
	yield().
	
	A task is just a function without parameters that can return a result. This is handled by
	a future in the code. Note that a task can also register tasks in the pool.


USAGE:
	ThreadPool pool;

	//register a simple task
	pool.RegisterTask([](){});

	//register a task that create a dependency or returns a result.
	auto my_future = pool.RegisterTrackedTask(my_task);
	...
	
	my_future.wait();
	//task is completed, i can execute tasks that depend on this.


	//register one or multiple task inside a task. This can be useful if you need to split some computation inside
	//a task.
	pool.RegisterTask([&]()
		{
			pool.RegisterTask(...);
		});


TODO:
	-Implement work steal.
	-Implement parallel loop.
	-Improve thread synchronization between threads with dependent task.
	-Discuss if it is necessary to register tasks with function arguments.		
*/

export module gargantua.parallel.thread_pool;

import <thread>;
import <stop_token>;
import <future>;
import <vector>;
import <concepts>;
import <type_traits>;
import <utility>;
import <functional>;
import <queue>;

import :function_wrapper;

import gargantua.types;
import gargantua.datastructures.concurrent_queue;

namespace gargantua::parallel
{
	export class ThreadPool
	{
	public:

		ThreadPool();

		/*
		* Register a task (a callable object) to be executed by a thread.
		* 
		* task: a callable object that is also movable.
		*/
		template <typename F>
			requires std::move_constructible<F> && std::invocable<F>
		auto RegisterTask(F task) -> void
		{
			FunctionWrapper f{ std::move(task) };

			if (IsWorkerThread()) //[[likely]]
			{
				local_queue->emplace(std::move(f));
			}
			else
			{
				pool_queue.Push(std::move(f));
			}
		}
		

		/*
		* Register a tracked task to be executed by a thread.
		* 
		* tracked_task: a callable object that is also movable.
		* 
		* return: a future linked to the task.
		*/
		template <typename F>
			requires std::move_constructible<F> && std::invocable<F>
		[[nodiscard]]
		auto RegisterTrackedTask(F tracked_task) -> std::future<std::invoke_result_t<F>>
		{
			using result_t = std::invoke_result_t<F>;
			std::packaged_task<result_t()> task{ std::move(tracked_task) };
			std::future<result_t> future{ task.get_future() };
			FunctionWrapper f{ std::move(task) };

			if (IsWorkerThread()) 
			{
				local_queue->emplace(std::move(f));
			}
			else
			{
				pool_queue.Push(std::move(f));
			}

			return future;
		}
		

		auto ParallelLoop() -> void;


	private:
		datastructures::ConcurrentQueue<FunctionWrapper> pool_queue;
		
		inline static thread_local UniqueRes<std::queue<FunctionWrapper>> local_queue;
		
		/* 
		* Note that the order is important! The pool must be destroyed the first.
		*/
		std::vector<std::jthread> threads;
		

	private:
		/*
		* This is the main function executed by the worker thread.
		* In this function the local queue is initialized (so the main thread doesn't have a local queue).
		*/
		auto WorkerThread(std::stop_token stop_work) -> void;

		/*
		* Check if the thread that is calling the function is a worker thread or the main thread.
		* This check is useful to see if the local queue can be used or not.
		*/
		[[nodiscard]]
		auto IsWorkerThread() -> bool
		{
			return local_queue != nullptr;
		}

	};
} //namespace gargantua::parallel