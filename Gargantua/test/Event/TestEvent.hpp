#pragma once

#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Core/EventSystem.hpp"

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
				auto ers = event_system.GetEventRegisterSystem();
				auto els = event_system.GetEventListenerSystem();

				ers->RegisterEvent<TestEvent1>();
				ers->RegisterEvent<TestEvent1>();
				ers->RegisterEvent<TestEvent2>();


				els->RegisterListener<TestEvent1>([](const Event::BaseEvent& e)
					{
						GRG_CORE_DEBUG("Inside Lambda for TestEvent1");
					});

				els->RegisterListener<TestEvent2>([](const Event::BaseEvent& e)
					{
						GRG_CORE_DEBUG("Inside Lambda for TestEvent2");
					});

				event_system.ProcessEvents();
				event_system.ProcessEvents();
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
			Core::EventSystem event_system;
		};
	} //namespace Test
} //namespace Gargantua