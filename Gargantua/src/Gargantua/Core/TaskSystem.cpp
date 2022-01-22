#include "TaskSystem.hpp"

#include <system_error>

namespace Gargantua
{
	namespace Core
	{
		TaskSystem::TaskSystem() : done(false)
		{
			natural_t num_of_threads = std::thread::hardware_concurrency();
			workers.reserve(num_of_threads);

			try
			{
				for (natural_t i = 0; i < num_of_threads; ++i)
				{
					workers.emplace_back(&TaskSystem::ExecuteTask, this);
				}
			}
			catch (std::system_error& e)
			{
				done = true;
				throw e;
			}
		}

		
		TaskSystem::~TaskSystem()
		{
			done = true;
		}


		void TaskSystem::ExecuteTask()
		{
			UniqueRes<Parallel::Task> task;
			while (!done)
			{
				if (tasks.TryPop(task))
				{
					(*task)();
				}
				else
				{
					//TODO: sleep, yield or what? 
					std::this_thread::yield();
				}
			}
		}

		//BAD, JUST TEMPORARRY.
		void TaskSystem::WaitForAllTasks()
		{
			while (!tasks.IsEmpty())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
			}
		}
	}
}