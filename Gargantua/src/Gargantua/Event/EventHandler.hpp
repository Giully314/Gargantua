#pragma once

#include "Gargantua/Core/EngineLogger.hpp"

#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Types.hpp"
#include "Gargantua/Concepts/Event.hpp"
#include "Gargantua/Generators/SequentialNumberGenerator.hpp"

#include <queue>
#include <unordered_map>
#include <functional>
#include <vector>
#include <algorithm>
#include <ranges>


namespace Gargantua
{
	namespace Event
	{
		/*
		Simple event dispatch based on a queue. The events are registered and processed later. There is the possilibity to 
		register a blocking event.
		A system can register a function that is executed when a particular type of event is processed.
		*/

		using event_callback_t = std::function<void(const BaseEvent&)>;

		struct EventCallbackHandle
		{
			natural_t id;
			event_callback_t f;
		};


		class EventHandler
		{
		public:

			//Register an event to the queue. This event will be processed when the ProcessEvents function is called.
			template <Concepts::Event T>
			void RegisterEvent(UniqueRes<T> event)
			{
				GRG_CORE_DEBUG("Register event {}", T::EventName);
				event_queue.push(std::move(event));
			}

			template <Concepts::Event T, typename ...Args>
			void RegisterEvent(Args&& ...args)
			{
				GRG_CORE_DEBUG("Register event {}", T::EventName);
				event_queue.push(CreateUniqueRes<T>(std::forward<Args>(args)...));
			}


			//Block the execution of the current thread to process immediately the event.
			template <Concepts::Event T>
			void RegisterBlockingEvent(UniqueRes<T> event)
			{
				GRG_CORE_DEBUG("Register blocking event {}", T::EventName);
				ProcessEvent(*event);
			}

			template <Concepts::Event T, typename ...Args>
			void RegisterBlockingEvent(Args&& ...args)
			{
				GRG_CORE_DEBUG("Register blocking event {}", T::EventName);
				auto event = CreateUniqueRes<T>(std::forward<Args>...);
				ProcessEvent(*event);
			}

			/*
			Return an id associated to the listener. This id is used to remove the listener in the future.
			*/
			template <Concepts::Event T>
			natural_t RegisterListener(event_callback_t f)
			{
				GRG_CORE_DEBUG("Register event listener for {}", T::EventName);
				natural_t id = sqg.Get();
				callbacks[T::EventName].push_back(EventCallbackHandle{ id, std::move(f) });
				return id;
			}


			template <Concepts::Event T>
			void UnregisterListener(natural_t id)
			{
				GRG_CORE_DEBUG("Unregister event listener for {}", T::EventName);
				auto& v = callbacks[T::EventName];
				const auto ret = std::ranges::remove_if(v, [&](auto& listener) {
					return id == listener.id;
					});
				v.erase(ret.begin(), ret.end());
			}

			void ProcessEvents();
			

		private:
			std::queue<UniqueRes<BaseEvent>> event_queue;
			std::unordered_map<BaseEvent::event_name_t, std::vector<EventCallbackHandle>> callbacks;
			Generators::SequentialNumberGenerator<natural_t> sqg;

			void ProcessEvent(const BaseEvent& event);
		};
	} //namespace Event
} //namespace Gargantua

