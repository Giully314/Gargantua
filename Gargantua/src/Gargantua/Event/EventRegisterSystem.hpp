#pragma once

#include "Gargantua/Types.hpp"
#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Concepts/Event.hpp"


#include <deque>
#include <utility>

namespace Gargantua
{
	namespace Event
	{
		/*
		Register events to the queue. For manipulate the events (extract or other operations), use an EventRegisterHandler.	
		*/
		class EventRegisterSystem
		{
		public:
			friend class EventRegisterHandler;


			//Register an event to the queue. 
			template <Concepts::Event T>
			void RegisterEvent(UniqueRes<T> event)
			{
				event_queue.push_back(std::move(event));
			}

			template <Concepts::Event T, typename ...Args>
			void RegisterEvent(Args&& ...args)
			{
				event_queue.push_back(CreateUniqueRes<T>(std::forward<Args>(args)...));
			}
			
		private:
			std::deque<UniqueRes<BaseEvent>> event_queue;
		};		
	} //namespace Event
} //namespace Gargantua


