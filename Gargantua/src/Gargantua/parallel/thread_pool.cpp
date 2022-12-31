/*
gargantua/parallel/thread_pool.cpp
*/

module gargantua.parallel.thread_pool;


namespace gargantua::parallel
{
	ThreadPool::ThreadPool()
	{
		natural_t num_of_threads = std::thread::hardware_concurrency();
		threads.reserve(num_of_threads);

		//Initialize the threads.
		try
		{
			for (natural_t i = 0; i < num_of_threads; ++i)
			{
				threads.emplace_back(std::bind_front(&ThreadPool::WorkerThread, this));
			}
		}
		catch (...)
		{
			//log the error of being unable to initialize the threads
			throw;
		}
	}



	auto ThreadPool::WorkerThread(std::stop_token stop_work) -> void
	{
		local_queue = CreateUniqueRes<std::queue<FunctionWrapper>>();

		FunctionWrapper task;


		while (!stop_work.stop_requested())
		{
			//Try first to get a task from the local queue;
			if (local_queue && !local_queue->empty())
			{
				task = std::move(local_queue->front());
				local_queue->pop();
				task();
			}
			//else try from the global queue.
			else if (pool_queue.TryPop(task))
			{
				task();
			}
			else
			{
				//TODO: change this to use a condition variable. (it's a good idea?)
				std::this_thread::yield();
			}
		}
	}
} //namespace gargantua::parallel