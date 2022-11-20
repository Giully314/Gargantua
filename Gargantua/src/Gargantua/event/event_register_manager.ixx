/*
gargantua/event/event_register_manager.ixx

PURPOSE: Handle low level event register.


CLASSES:
	EventRegisterManager: Handle the process of registering an event in the event queue.


DESCRIPTION:
	The EventRegisterManager manages only one operation: register an event to a queue.
	There are functions that allow to access these events to be read and manipulated. It is important to clear
	the queue after processing the events.


USAGE:
	EventRegisterManager evt_reg;
	evt_reg.RegisterEvent<MyEvent>(args);

	auto event_views = evt_reg.GetEventsView();

	for (auto& e : event_views | filter_only_input_events_adaptor)
	{
		//process only the input events.
	}



TODO:
	-specify directly what types of events to extract. For example,
	template <Event T>
	auto GetSpecificView()
	{
		return event_queue | std::views::filter(T);
	}


	-test if there is the need to add a time of execution. This can be added if the events are a lot and there is
	too much time spent on resolving them.

*/

module;

/*
I don't know why only in this file i can't import array because it gives me the error 
"undefined std::array". In other files the import <array> works.
*/
#include <array>

export module gargantua.event.event_register_manager;

import <deque>;
import <utility>;
import <concepts>;
import <ranges>;
import <memory>;
import <algorithm>;

import gargantua.types;
import gargantua.event.events;

export namespace gargantua::event
{

	class EventRegisterManager
	{
	public:
		EventRegisterManager() = default;

		EventRegisterManager(const EventRegisterManager&) = delete;
		EventRegisterManager& operator=(const EventRegisterManager&) = delete;

		EventRegisterManager(EventRegisterManager&&) = default;
		EventRegisterManager& operator=(EventRegisterManager&&) = default;


		/*
		* Register an event of type T to the event queue.
		* The type T must satisfy the Event concept.
		*
		* Complexity: O(1).
		*/
		template <Event T, typename ...Args>
			requires std::constructible_from<T, Args...>
		auto RegisterEvent(Args&& ...args) -> void
		{
			event_queues[static_cast<int>(current_active_queue)].emplace_back(CreateUniqueRes<T>(std::forward<Args>(args)...));
		}


		/*
		* Unregister the first event of type T in the current active queue.
		* Complexity: O(queue.size()).
		*/
		template <Event T>
		auto UnregisterEvent() -> void
		{
			auto& current_queue = event_queues[static_cast<int>(current_active_queue)];
			auto it = std::ranges::find_if(current_queue,
				[](const UniqueRes<BaseEvent>& e)
				{
					return e->GetEventName() == T::EventName;
				});
			
			if (it != current_queue.end())
			{
				current_queue.erase(it);
			}
		}


		/*
		* Unregister all the events of type T in the current active queue.
		* Complexity: O(queue.size()).
		*/
		template <Event T>
		auto UnregisterAllEvents() -> void
		{
			std::erase_if(event_queues[static_cast<int>(current_active_queue)], 
				[](const UniqueRes<BaseEvent>& e)
				{
					return e->GetEventName() == T::EventName;
				});
		}


		/*
		* A view to operate on the events. Keep in mind that events are read only information.
		* Complexity: O(1).
		*/
		auto GetCurrentQueueEventView()
		{
			return event_queues[static_cast<int>(current_active_queue)] | std::views::all;
		}


		auto GetCurrentEventQueue() -> std::deque<UniqueRes<BaseEvent>>&
		{
			return event_queues[static_cast<int>(current_active_queue)];
		}


		/*
		* This function must be called at the end of the event processing to clear the queue.
		* Complexity: O(1).
		*/
		auto ClearCurrentEventQueue() -> void
		{
			event_queues[static_cast<int>(current_active_queue)].clear();
		}


		/*
		* Swap the current active queue.
		* Complexity: O(1).
		*/
		auto SwapQueue() -> void
		{
			current_active_queue = !current_active_queue;
		}


	private:
		std::array<std::deque<UniqueRes<BaseEvent>>, 2> event_queues;
		bool current_active_queue = false;
	}; //class EventRegisterManager
} //namespace gargantua::event


