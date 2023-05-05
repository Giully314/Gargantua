/*
* gargantua/platform/event_dispatcher.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* The event dispatcher is a blocking event handler used for platform events like input, window resize and so on.
* The type of events is handled by a simple enum, because it is known at compile time what these events are.
* 
* 
* TODO: 
* - Add the opportunity to remove a listener. Even though if a listener is registered for this type of events it probably needs to
*	listen to them for all the duration of the program, there could be situations in which it is temporary to listen to these events.
* 
*/

export module gargantua.platform.event_dispatcher;

import <tuple>;
import <vector>;
import <typeinfo>;
import <typeindex>;
import <functional>;
import <concepts>;
import <utility>;



import gargantua.platform.platform_events;
import gargantua.types;
import gargantua.mpl.type_list;

namespace gargantua::platform
{
	// Typelist used inside the event dispatcher to register at compile time all the platform events.
	using PlatformEvents = mpl::TypeList<
		KeyEvent, KeyPressedEvent, KeyReleasedEvent,
		WindowResizeEvent, WindowCloseEvent,
		MouseButtonEvent, MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseCursorEvent,
		MouseWheelScrollEvent>;

	template <Event TEvent>
	struct IsEvent
	{
		static constexpr bool Value = true;
	};

	template <Event TEvent> 
	struct TupleElementType
	{
		TupleElementType() : type_id(typeid(TEvent))
		{

		}

		std::type_index type_id;
		std::vector<std::function<void(const TEvent&)>> listeners;
	};

	template <Event TEvent> 
	struct GetTupleElementType
	{
		using Type = TupleElementType<TEvent>;
	};


	export 
	class PlatformEventDispatcher : public Singleton<PlatformEventDispatcher>
	{
	public:
		template <Event TEvent> 
		using ListenerFunction = std::function<void(const TEvent&)>;

		// Dispatch an event to all the listeners.
		// Running time: O(num of listeners * work_done).
		template <Event TEvent> 
		auto Dispatch(const TEvent& event) -> void
		{
			auto& e = GetTupleElement<TEvent>();
			for (auto& f : e.listeners)
			{
				f(event);
			}
		}

		// Create an event with the passed arguments and dispatch it to all the listeners.
		// Running time: O(num of listeners * work_done).
		template <Event TEvent, typename ...Args>
			requires std::constructible_from<TEvent, Args...>
		auto Dispatch(Args&& ...args) -> void
		{
			const TEvent event{ std::forward<Args>(args)... };
			auto& e = GetTupleElement<TEvent>();
			for (auto& f : e.listeners)
			{
				f(event);
			}
		}

		
		template <Event TEvent, typename F>
			requires std::invocable<F, TEvent>
		auto RegisterListener(F&& listener) -> void
		{
			auto& e = GetTupleElement<TEvent>();
			e.listeners.emplace_back(std::forward<F>(listener));
		}

	private:
		template <Event TEvent> 
		[[nodiscard]] 
		auto GetTupleElement() -> TupleElementType<TEvent>&
		{
			return std::get<TupleElementType<TEvent>>(event_listeners);
		}

	private:
		// This declaration applies 2 meta function: 
		// 1) transform every event into a TupleElementType; 
		// 2) rebind the type from typelist to tuple.
		using event_listeners_tuple = mpl::RebindT<mpl::TransformT<PlatformEvents, GetTupleElementType>, std::tuple>;
		event_listeners_tuple event_listeners;
	};
} // namespace gargantua::platform