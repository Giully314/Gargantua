#pragma once
/*
Gargantua/Systems/TaskSystem.hpp

PURPOSE: Multithreading task execution.

CLASSES:
	TaskSystem: 


TODO:
	Refactor this class when must be used. For now i don't need multithreading.
*/

#include "Gargantua/Types.hpp"
#include "Gargantua/DataStructures/ConcurrentQueue.hpp"
#include "Gargantua/Parallel/Task.hpp"
#include "Gargantua/Parallel/LambdaTask.hpp"

#include <thread>
#include <stop_token>
#include <vector>
#include <atomic>
#include <future>
#include <type_traits>
#include <concepts>
#include <chrono>


namespace Gargantua
{
	namespace Systems
	{
		//TODO: allows to register tracked task/lambda
		class TaskSystem
		{
		public:
			~TaskSystem();
			

			template <typename T, typename ...Args>
			requires std::derived_from<T, Parallel::Task>
			void AddTask(Args&& ...args)
			{
				tasks.Push(CreateUniqueRes<T>(std::forward<Args>(args)...));
			}


			template <typename T>
			requires std::derived_from<T, Parallel::Task>
			void AddTask(UniqueRes<T> task)
			{
				tasks.Push(std::move(task));
			}

			
			template <typename F, typename ...Args>
			requires std::invocable<F, Args...> && std::movable<F> 
			void AddLambda(F&& f, Args&& ...args)
			{
				tasks.Push(CreateUniqueRes<Parallel::LambdaTask<F, Args...>>(std::move(f), std::forward<Args>(args)...));
			}


			static TaskSystem* Instance() 
			{
				static TaskSystem* singleton = new TaskSystem();
				return singleton; 
			}

			//TODO: HOW TO WAIT FOR ALL CURRENT TASKS TO COMPLETE?
			//MAYBE ADD A FUNCTION TO THE QUEUE?
			void WaitForAllTasks();

		private:
			DataStructures::ConcurrentQueue<UniqueRes<Parallel::Task>> tasks;
			std::vector<std::jthread> workers;
			std::atomic_bool done;
		

			TaskSystem();
			void ExecuteTask();
		};
	} //namespace Systems
} //namespace Gargantua