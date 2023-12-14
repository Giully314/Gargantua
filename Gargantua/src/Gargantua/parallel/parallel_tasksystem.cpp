/*
* gargantua/parallel/parallel_tasksystem.cpp
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.parallel.task_system;

import gargantua.log;

namespace gargantua::parallel
{
	TaskSystem::~TaskSystem()
	{
		Shutdown();
	}


	auto TaskSystem::Startup() -> void
	{
		u32 thread_count = std::thread::hardware_concurrency();
		GRG_CORE_DEBUG("TaskSystem startup with {} threads.", thread_count);
		threads.reserve(thread_count);
		try
		{
			for (u32 i = 0; i < thread_count; ++i)
			{
				threads.emplace_back(&TaskSystem::WorkerThread, this, stop_source);
			}
		}
		catch (...)
		{

			throw;
		}
	}

	auto TaskSystem::Shutdown() -> void
	{
		StopWorkers();
	}


	auto TaskSystem::RunPendingTask() -> void 
	{
		if (local_tasks_queue && !local_tasks_queue->empty())
		{
			Task t = std::move(local_tasks_queue->front());
			local_tasks_queue->pop();
			t();
		}
		else if (auto ot = pool_tasks_queue.TryPop(); ot)
		{
			(*ot)();
		}
		else
		{
			std::this_thread::yield();
		}
	}


	auto TaskSystem::WorkerThread(std::stop_source stop_source) -> void
	{
		local_tasks_queue = CreateUniqueRes<local_queue_type>();
		std::stop_token stop_token = stop_source.get_token();

		while (!stop_token.stop_requested())
		{
			RunPendingTask();
		}
	}
} // namespace gargantua::parallel