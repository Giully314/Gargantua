/*
gargantua/system/event_system.ixx

PURPOSE: Event system.


CLASSES:
	EventSystem: Event system using the Event components.


DESCRIPTION:
	Simple event dispatch based on a queue. The events are registered and processed later.
	A system can register a function that is executed when a particular type of event is processed.


TODO: Add the possilibity to register a blocking event or make another class to do that.

*/

export module gargantua.system.event_system;

import gargantua.types;

import gargantua.event.events;
import gargantua.event.event_manager;

import <functional>;
import <utility>;
import <concepts>;


export namespace gargantua::system
{

	using event_callback_t = std::function<void(const event::BaseEvent&)>;


	class EventSystem
	{
	public:
		EventSystem() = default;
		
		/*
		* TODO: REMOVE THIS AND REFACTOR THE WAY THE EVENTS ARE BLOCKED BASED ON THE TYPE
		*/
		/*auto BlockInputEvents(bool block) -> void
		{
			block_input_events = block;
		}*/


		auto ProcessEvents() -> void;


		template <event::Event T, typename ...Args>
			requires std::constructible_from<T, Args...> 
		auto RegisterEvent(Args&& ...args) -> void
		{
			event_reg_mng.RegisterEvent<T, Args...>(std::forward<Args>(args)...);
		}


		template <event::Event T>
		auto RegisterListener(event_callback_t f) -> natural_t
		{
			return event_list_mng.RegisterListener<T>(std::move(f));
		}

		template <event::Event T>
		auto UnregisterListener(natural_t id) -> void
		{
			event_list_mng.UnregisterListener(id);
		}


	private:
		event::EventRegisterManager event_reg_mng;
		event::EventListenerManager event_list_mng;
	}; //class EventSystem

} //namespace gargantua::system

