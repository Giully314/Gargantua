module;

#include <iostream>

module gargantua.test.system.test_event_system;

namespace gargantua::test
{
	auto TestEventSystem::GenerateEvents() -> void
	{
		logger.Debug("GenerateEvents");

		event_sys.RegisterEvent<TestEvent>();

		event_sys.RegisterEvent<TestEvent0>();
		event_sys.RegisterEvent<TestEvent0>();
		event_sys.RegisterEvent<TestEvent0>();
		event_sys.RegisterEvent<TestEvent0>();

		event_sys.RegisterEvent<TestEvent1>();
		event_sys.RegisterEvent<TestEvent1>();
		event_sys.RegisterEvent<TestEvent1>();

		event_sys.RegisterEvent<TestEvent2>();
		event_sys.RegisterEvent<TestEvent2>();
		event_sys.RegisterEvent<TestEvent2>();
	}

	auto TestEventSystem::GenerateListeners() -> void
	{
		logger.Debug("GenerateListeners");

		event_sys.RegisterListener<TestEvent>(
			[&](const event::BaseEvent& e) -> void
			{
				const TestEvent& te = static_cast<const TestEvent&>(e);

				logger.Debug("{}", te.i);

				event_sys.RegisterEvent<TestEvent0>();

				event_sys.RegisterEvent<TestEvent1>();

				event_sys.RegisterEvent<TestEvent2>();
			}
		);


		event_sys.RegisterListener<TestEvent0>(
			[&](const event::BaseEvent& e) -> void
			{
				const TestEvent0& te = static_cast<const TestEvent0&>(e);
				
				logger.Debug("{}", te.i);
			}
		);


		event_sys.RegisterListener<TestEvent1>(
			[&](const event::BaseEvent& e) -> void
			{
				const TestEvent1& te = static_cast<const TestEvent1&>(e);
				
				logger.Debug("{}", te.i);
			}
		);


		event_sys.RegisterListener<TestEvent2>(
			[&](const event::BaseEvent& e) -> void
			{
				const TestEvent2& te = static_cast<const TestEvent2&>(e);
				
				logger.Debug("{}", te.i);
			}
		);
	}


	auto TestEventSystem::RunTest() -> void
	{
		logger.Debug("RunTest");
		GenerateListeners();
		GenerateEvents();

		logger.Debug("ProcessEvents");
		event_sys.ProcessEvents();

		logger.Debug("ProcessEvents");
		event_sys.ProcessEvents();
	}
} // namespace gargantua::test