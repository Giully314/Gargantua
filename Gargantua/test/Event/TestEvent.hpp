#pragma once

#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Event/EventHandler.hpp"

#include <string>
#include <functional>

namespace Gargantua
{
	namespace Test
	{
		struct TestEvent1 : public Event::BaseEvent
		{

			inline static const std::string EventName{ "TestEvent1" };
			GET_EVENT_NAME
		};

		struct TestEvent2 : public Event::BaseEvent
		{

			inline static const std::string EventName{ "TestEvent2" };
			GET_EVENT_NAME
		};

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
		class TestEvent
		{
		public:
			TestEvent() = default;

			
			void RunTest()
			{
				auto id1 = event_handler.RegisterListener<TestEvent1>(BIND_FN(TestEvent::OnTestEvent1));
				auto id2 = event_handler.RegisterListener<TestEvent2>(BIND_FN(TestEvent::OnTestEvent2));

				event_handler.RegisterEvent<TestEvent1>();
				event_handler.RegisterEvent<TestEvent2>();

				event_handler.ProcessEvents();

				event_handler.UnregisterListener<TestEvent1>(id1);
				event_handler.UnregisterListener<TestEvent2>(id2);

				event_handler.RegisterBlockingEvent<TestEvent1>();
				event_handler.RegisterBlockingEvent<TestEvent2>();
			}


			void OnTestEvent1(const Event::BaseEvent& e)
			{
				GRG_CORE_DEBUG("Inside OnTestEvent1");
				const TestEvent1& te1 = static_cast<const TestEvent1&>(e);	
			}

			void OnTestEvent2(const Event::BaseEvent& e)
			{
				GRG_CORE_DEBUG("Inside OnTestEvent2");
				const TestEvent2& te1 = static_cast<const TestEvent2&>(e);
			}

		private:
			Event::EventHandler event_handler;
		};
	} //namespace Test
} //namespace Gargantua