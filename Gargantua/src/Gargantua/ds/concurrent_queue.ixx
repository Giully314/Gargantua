/*
* gargantua/ds/concurrent_queue.ixx
* 
* PURPOSE: multithread queue.
* 
* CLASSES:
*	ConcurrentQueue: a lock based queue for concurrent accesses.
* 
* DESCRIPTION:
*	Straightforward implementation of a concurrent queue using mutex and conditional variable. The implementation
*	can be found on "C++ concurrency in action" (note that it's different from the book, I changed the API a  
*	little bit using a more direct approach with returning values).
* 
*/

export module gargantua.ds.concurrent_queue;

import <concepts>;
import <mutex>;
import <deque>;
import <condition_variable>;
import <optional>;
import <utility>;


namespace gargantua::ds
{	
	export 
	template <std::movable T>
	class ConcurrentQueue
	{
	public:
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
		using iterator = typename std::deque<T>::iterator;
		using const_iterator = typename std::deque<T>::const_iterator;
		using difference_type = typename std::deque<T>::difference_type;
		using size_type = typename std::deque<T>::size_type;


		ConcurrentQueue() = default;

		ConcurrentQueue(ConcurrentQueue&&) = default;
		auto operator=(ConcurrentQueue&&) -> ConcurrentQueue& = default;


		template <typename U>
			requires std::constructible_from<T, U>
		auto push(U&& new_value) -> void
		{
			std::lock_guard lk(mut);
			queue.emplace_back(std::forward<U>(new_value));
			cond.notify_one();
		}



		auto wait_and_pop() -> value_type
		{
			std::unique_lock lk(mut);
			cond.wait(lk, [this]() {return !queue.empty(); });
			auto value = std::move(queue.front());
			queue.pop_front();
			return value;
		}


		auto try_pop() -> std::optional<value_type>
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


		auto empty() const -> bool
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
		std::deque<T> queue;
	};
} // namespace gargantua::ds


