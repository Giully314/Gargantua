/*
gargantua/dataStructures/concurrent_queue.ixx


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

export module gargantua.datastructures.concurrent_queue;


import <mutex>;
import <condition_variable>;
import <queue>;
import <concepts>;

namespace gargantua::datastructures
{
	export template <std::movable T>
	class ConcurrentQueue
	{
	public:
		ConcurrentQueue() = default;


		auto Push(T new_value) -> void
		{
			std::lock_guard lk(mut);
			queue.push(std::move(new_value));
			cond.notify_one();
		}

		auto WaitAndPop(T& value) -> void
		{
			std::unique_lock lk(mut);
			cond.wait(lk, [this]() {return !queue.empty(); });
			value = std::move(queue.front());
			queue.pop();
		}


		auto TryPop(T& value) -> bool
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


		auto IsEmpty() const -> bool
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
	}; //class ConcurrentQueue

} //namespace gargantua::datastructures