
export module gargantuatest.event.test_event_dispatcher;

import <cassert>;

import gargantua.event;


import gargantuatest.testbase;
import gargantuatest.event.test_events;

namespace gargantuatest
{
	using namespace gargantua::event;
	
	export class EventDispatcherTest final : private TestBase
	{
	public:

		void RunTest()
		{
			using namespace gargantua::event;
			logger.Debug("Start EventDispatcherTest");

			int id1 = 12;
			int id2 = 4;
			int id3 = 4;
			int id4 = 5;
			int id_to_remove = id3;

			dispatcher.RegisterListener<TestEvent1>([&](const BaseEvent& e)
				{
					const auto& e1 = static_cast<const TestEvent1&>(e);
					assert((e1.s == "TestEvent1"));
					logger.Debug("TestEvent1 OK");
				}, 
				id1);

			dispatcher.RegisterListener<TestEvent2>([&](const BaseEvent& e)
				{
					const auto& e1 = static_cast<const TestEvent2&>(e);
					assert((e1.s == "TestEvent2"));
					logger.Debug("TestEvent2 OK");
				}, 
				id2);

			dispatcher.RegisterListener<TestEvent3>([&](const BaseEvent& e)
				{
					const auto& e1 = static_cast<const TestEvent3&>(e);
					assert((e1.s == "TestEvent3"));
					logger.Debug("TestEvent3 OK");
				},
				id3);

			dispatcher.RegisterListener<TestEvent4>([&](const BaseEvent& e)
				{
					const auto& e1 = static_cast<const TestEvent4&>(e);
					assert((e1.s == "TestEvent4"));
					logger.Debug("TestEvent4 OK with value x {}", e1.x);
				},
				id4);

			TestEvent1 e1;
			TestEvent2 e2;
			TestEvent3 e3;

			dispatcher.Dispatch<TestEvent1>(e1);
			dispatcher.Dispatch<TestEvent2>(e2);
			dispatcher.Dispatch<TestEvent3>(e3);
			dispatcher.Dispatch<TestEvent4>(123);

			dispatcher.UnregisterListeners(id_to_remove);

			logger.Debug("Dispatch events after unregistering listeners with id {}", id_to_remove);
			dispatcher.Dispatch<TestEvent1>(e1);
			dispatcher.Dispatch<TestEvent2>(e2);
			dispatcher.Dispatch<TestEvent3>(e3);
			dispatcher.Dispatch<TestEvent4>(123);
			
			logger.Debug("End EventDispatcherTest");
		}

	private:
		EventDispatcher dispatcher;
	};
} // namespace gargantuatest