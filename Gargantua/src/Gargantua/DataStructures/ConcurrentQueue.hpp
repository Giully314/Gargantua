#pragma once
/*
Gargantua/DataStructures/ConcurrentQueue.hpp


PURPOSE: Queue for multithreading usage.

CLASSES:
	ConcurrentQueue: an std::queue with lock.

DESCRIPTION:
	Thread safe queue with notification (condition variable) that wake up other threads when an element is
	pushed into the queue.
	Note: This data structure is implemented in the book "C++ Concurrency in Action" by Anthony Williams.

USAGE:
	ConcurrentQueue<MyType> q;

	Thread1: q.Push(value);
	Thread2: q.WaitAndPop(variable);
*/

#include <mutex>
#include <condition_variable>
#include <queue>
#include <concepts>


namespace Gargantua
{
	namespace DataStructures
	{
		template <std::movable T>
		class ConcurrentQueue
		{
		public:
			ConcurrentQueue() = default;


			void Push(T new_value)
			{
				std::lock_guard lk(mut);
				queue.push(std::move(new_value));
				cond.notify_one();
			}

			void WaitAndPop(T& value)
			{
				std::unique_lock lk(mut);
				cond.wait(lk, [this]() {return !queue.empty(); });
				value = std::move(queue.front());
				queue.pop();
			}


			bool TryPop(T& value)
			{
				std::lock_guard lk(mut);
				if (queue.empty())
				{
					return false;
				}

				value = std::move(queue.front());
				queue.pop();
				return true;
			}


			bool IsEmpty() const
			{
				std::lock_guard lk(mut);
				return queue.empty();
			}


			//void WaitUntilEmpty()
			//{
			//	std::unique_lock lk(mut);
			//	cond.wait(lk, [this]() {return queue.empty(); });
			//}


		private:
			mutable std::mutex mut;
			std::condition_variable cond;
			std::queue<T> queue;
		};
	} //namespace DataStructures
} //namespace Gargantua