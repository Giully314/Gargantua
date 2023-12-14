/*
* gargantua/event/event_dispatcher.ixx
* 
* PURPOSE: blocking dispatcher.
* 
* CLASSES:
*	EventDispatcher: blocking dynamic dispatcher.
*	CallbackInfo: callback and id (used to unregister the listener).
* 
* DESCRIPTION:
*	This component provides a blocking dynamic event dispatcher that can be used to listen to specific events,
*	dispatch an event, unregister a listener (optional using an id passed by the caller).	
*	For more on events check the event_baseevent.ixx file.
* 
* USAGE:
*	EventDispatcher evd;
*	
*	// In this case i want to pass an id to remove this listener later.
*	evd.RegisterListener<MyWindowEvent>([](const BaseEvent& e)
*			{
*				// We can static_cast the event because we know for sure that the type of e is the same as 
*				// the type we are listening for (in this case MyWindowEvent).
*				const auto& we = static_cast<const MyWindowEvent&>(e);
*			}, 
*			my_id);
* 
*	
*	// All the listeners will be notified (in the order of insertion) about this event.
*	evd.Dispatch<MyWindowEvent>(info); 
*	
*	// Not interested anymore on listening to this event.
*	evd.UnregisterListener<MyWindowEvent>(my_id); 
*/

module;

#include <gargantua/log/logger_macro.hpp>

export module gargantua.event.event_dispatcher;

import <typeinfo>;
import <typeindex>;
import <unordered_map>;
import <vector>;
import <functional>;
import <utility>;


import gargantua.types;
import gargantua.log;
import gargantua.event.concepts;
import gargantua.event.base_event;

namespace gargantua::event
{
	using EventListenerID = i32;
	using EventCallbackFn = std::function<void(const BaseEvent&)>;

	struct CallbackInfo
	{
		explicit CallbackInfo(EventCallbackFn f, const EventListenerID id_) : 
			listener(std::move(f)), id(id_) { }


		EventCallbackFn listener;
		
		// The id is used in case the listener must be unregistered. 
		EventListenerID id{ -1 };
	};


	export class EventDispatcher : NonCopyable
	{
	public:

		/*
		* Register a listener for the specified TEvent.
		* Precondition: id must be >= 0. 
		* A default id of -1 is used if there isn't the necessity to remove the listener.
		* Complexity: O(1).
		*/
		template <CEvent TEvent>
		auto RegisterListener(EventCallbackFn f, const EventListenerID id = -1) -> void
		{
			// If it doesn't exist, create a new vector of listeners for this event.
			GRG_CORE_DEBUG("Register listener with id {}", id);
			listeners[std::type_index{ typeid(TEvent) }].emplace_back(std::move(f), id);
		}


		/*
		* Remove the listeners with the associated id.
		* Precondition: id must be >= 0.
		* Complexity: O(num of listeners for TEvent).
		*/
		template <CEvent TEvent>
		auto UnregisterListener(const EventListenerID id) -> void
		{
			if (const auto it = listeners.find(std::type_index{ typeid(TEvent) }); it != listeners.cend()) [[likely]]
			{
				GRG_CORE_DEBUG("Unregister listeners with id {}", id);
				std::erase_if(it->second, [=](const CallbackInfo& c)
					{
						return c.id == id;
					});
			}
		}


		/*
		* Remove all the listeners with the associated id.
		* Precondition: id must be >= 0.
		* Complexity: O(number of listeners for TEvent * number of events).
		*/
		auto UnregisterListeners(const EventListenerID id) -> void
		{
			GRG_CORE_DEBUG("Unregister listeners with id {}", id);
			for (auto& el : listeners) 
			{
				std::erase_if(el.second, [=](const CallbackInfo& c)
					{
						return c.id == id;
					});
			}
		}


		/*
		* Dispatch the event to all the listeners.
		* Complexity: O(num of listeners).
		*/
		template <CEvent TEvent>
		auto Dispatch(const TEvent& e) const -> void
		{
			if (const auto it = listeners.find(std::type_index{ typeid(TEvent) }); it != listeners.cend())
			{
				//GRG_CORE_DEBUG("Dispatch event {}", typeid(TEvent).name());
				for (const auto& l : it->second)
				{
					l.listener(e);
				}	
			}
			
		}


		/*
		* Dispatch the event to all the listeners.
		* Complexity: O(num of listeners).
		*/
		template <CEvent TEvent, typename ...TArgs>
			requires std::constructible_from<TEvent, TArgs...>
		auto Dispatch(TArgs&& ...args) const -> void
		{
			if (const auto it = listeners.find(std::type_index{ typeid(TEvent) }); it != listeners.cend())
			{
				const TEvent e{ std::forward<TArgs>(args)... };
				//GRG_CORE_DEBUG("Dispatch event {}", typeid(TEvent).name());
				for (const auto& l : it->second)
				{
					l.listener(e);
				}
			}
		}

	private:	
		// TODO: unordered_map is SLOW, consider to use flatmap (not supported yet) or a custom implementation
		// based on vector.
		std::unordered_map<std::type_index, std::vector<CallbackInfo>> listeners;
	};
} // namespace gargantua::event
