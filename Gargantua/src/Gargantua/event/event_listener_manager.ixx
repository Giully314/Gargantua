/*
gargantua/event/event_listener_anager.ixx

PURPOSE: Manage event listeners.

CLASSES:
	EventListenerManager: Register listener for events.

DESCRIPTION:
	This class handles the low level operations for register/unregister listeners.

USAGE:
	event_register.RegisterListener<MyEvent>(my_listener);

*/

export module gargantua.event.event_listener_manager;

import <functional>;
import <unordered_map>;
import <vector>;
import <algorithm>;
import <utility>;
import <string>;
import <ranges>;
import <concepts>;

import gargantua.types;

import gargantua.event.events;

import gargantua.generator.natural_number_generator;


export namespace gargantua::event
{
	using event_callback_t = std::function<void(const BaseEvent&)>;


	class EventListenerManager
	{
	public:

		/*
		* Register a listener for an event T.
		* Return an id associated to the listener. This id is used to remove the listener in the future.
		* Complexity: O(1);
		*/
		template <Event T>
		auto RegisterListener(event_callback_t f) -> natural_t
		{
			natural_t id = sqg.Get();
			callbacks[T::EventName].push_back(std::make_pair(id, std::move(f)));
			return id;
		}


		/*
		* Unregister a listener for event T using its id.
		* 
		* Complexity: O(num of listeners for type T).
		* 
		* TODO: A better implementation (even though same O(n)) could be to find the single listener and
		* swap it with the last element, then pop. I can do this operation because it doesn't matter
		* the order of insertion (and so the order of listeners).
		*/
		template <Event T>
		auto UnregisterListener(natural_t id) -> void
		{
			auto& v = callbacks[T::EventName];
			const auto ret = std::ranges::remove_if(v, [&](auto& listener) {
				return id == listener.first;
				});
			v.erase(ret.begin(), ret.end());
		}

		/*
		* Unregister all listeners for event T.
		* Complexity: O(1).
		*/
		template <Event T>
		auto UnregisterAllListeners() -> void
		{
			callbacks[T::EventName].clear();
		}


		/*
		* Get a view of callbacks for an event T.
		* Complexity: O(1).
		*/
		/*template <Event T>
		constexpr auto GetListenersView()
		{
			return callbacks[T::EventName] | std::views::values;
		}*/

		/*
		* Get a view of all callbacks.
		* Complexity: O(1).
		*/
		auto GetListenersView(const std::string& event_name)
		{
			return callbacks[event_name] | std::views::values;
		}



	private:
		std::unordered_map<std::string, std::vector<std::pair<natural_t, event_callback_t>>> callbacks;
		gargantua::generator::NaturalNumberGenerator<natural_t> sqg;
	};

} //namespace gargantua::event


