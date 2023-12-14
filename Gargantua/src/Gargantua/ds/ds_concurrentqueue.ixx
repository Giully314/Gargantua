/*
* gargantua/ds/ds_concurrentqueue.ixx
* 
* PURPOSE: multithread safe queue.
* 
* CLASSES:
*	ConcurrentQueue: a lock based queue for concurrent access.
* 
* DESCRIPTION:
*	Straightforward implementation of a concurrent queue using mutex and conditional variable.
*/

export module gargantua.ds.concurrent_queue;

import <concepts>;
import <memory>;
import <mutex>;
import <deque>;
import <condition_variable>;
import <optional>;
import <utility>;

import gargantua.types;
import gargantua.mem.concepts;


namespace gargantua::ds
{	
	export template <std::movable T, mem::CAllocator TAllocator = std::allocator<T>>
	class ConcurrentQueue : NonCopyable
	{
	public:
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
		using iterator = typename std::deque<T>::iterator;
		using const_iterator = typename std::deque<T>::const_iterator;
		using difference_type = typename std::deque<T>::difference_type;
		using size_type = typename std::deque<T>::size_type;
		using allocator_type = TAllocator;

		/*
		* Push a value constructed by args in the queue.
		*/
		template <typename ...TArgs> 
			requires std::constructible_from<T, TArgs...>
		auto Push(TArgs&& ...args) -> void
		{
			std::lock_guard lk(mut);
			queue.emplace_back(std::forward<TArgs>(args)...);
			cond.notify_one();
		}


		/*
		* Wait until there is a value that can be popped from the queue.
		*/
		auto WaitAndPop() -> value_type
		{
			std::unique_lock lk(mut);
			cond.wait(lk, [this]() {return !queue.empty(); });
			auto value = std::move(queue.front());
			queue.pop_front();
			return value;
		}


		/*
		* Try to pop from the queue. If the queue is empty return a nullopt.
		*/
		auto TryPop() -> std::optional<value_type>
		{
			std::lock_guard lk(mut);
			if (queue.empty())
			{
				return std::nullopt;
			}

			std::optional<value_type> value{ std::move(queue.front()) };
			queue.pop_front();
			return value;
		}


		/*
		* Check if the queue is empty.
		*/
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



		// ************************ ITERATORS **************************************
		
		auto begin() noexcept -> iterator
		{
			return queue.begin();
		}

		auto end() noexcept -> iterator
		{
			return queue.end();
		}

		auto cbegin() const noexcept -> const_iterator
		{
			return queue.cbegin();
		}

		auto cend() const noexcept -> const_iterator
		{
			return queue.cend();
		}

		// ************************ ITERATORS **************************************


	private:
		mutable std::mutex mut;
		std::condition_variable cond;
		std::deque<T, TAllocator> queue;
	};
} // namespace gargantua::ds


