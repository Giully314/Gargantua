#pragma once

#include "Gargantua/Types.hpp"
#include "Gargantua/Concepts/Event.hpp"
#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Generators/SequentialNumberGenerator.hpp"


#include <functional>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <ranges>


namespace Gargantua
{
	namespace Event
	{

		using event_callback_t = std::function<void(const BaseEvent&)>;


		class EventListenerSystem
		{
		public:
			friend class EventListenerHandler;


			/*
			Return an id associated to the listener. This id is used to remove the listener in the future.
			*/
			template <Concepts::Event T>
			natural_t RegisterListener(event_callback_t f)
			{
				GRG_CORE_DEBUG("Register event listener for {}", T::EventName);
				natural_t id = sqg.Get();
				callbacks[T::EventName].push_back(std::make_pair( id, std::move(f) ));
				return id;
			}


			/*
			A better implementation (even though same O(n)) could be to find the single listener and 
			swap it with the last element, then pop. I can do this operation because it doesn't matter 
			the order of insertion (and so the order of listeners).
			*/
			template <Concepts::Event T>
			void UnregisterListener(natural_t id)
			{
				GRG_CORE_DEBUG("Unregister event listener for {}", T::EventName);
				auto& v = callbacks[T::EventName];
				const auto ret = std::ranges::remove_if(v, [&](auto& listener) {
					return id == listener.first;
					});
				v.erase(ret.begin(), ret.end());
			}


		private:
			std::unordered_map<std::string, std::vector<std::pair<natural_t, event_callback_t>>> callbacks;
			Generators::SequentialNumberGenerator<natural_t> sqg;
		};
	} //namespace Event
} //namespace Gargantua


