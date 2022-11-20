/*
gargantua/test/system/test_event_system.ixx

*/

module;

#include <gargantua/event/events_macro.hpp>

export module gargantua.test.system.test_event_system;

import gargantua.test.test_base;

import gargantua.types;

import gargantua.event.base_event;
import gargantua.event.event_concepts;

import gargantua.system.event_system;

import <string>;


export namespace gargantua::test
{
	struct TestEvent : public event::BaseEvent
	{
		TestEvent() = default;

		TestEvent(int i_) : i(i_) { }


		GET_EVENT_NAME

		int i = -1;

		inline static const std::string EventName{ "TestEvent" };
	};

	struct TestEvent0 : public TestEvent
	{
		TestEvent0() : TestEvent(0) { }
		
		TestEvent0(int i) : TestEvent(i) { }

		GET_EVENT_NAME

		inline static const std::string EventName{ "TestEvent0" };
	};


	struct TestEvent1 : public TestEvent
	{
		TestEvent1() : TestEvent(1) { }

		TestEvent1(int i) : TestEvent(i) { }

		GET_EVENT_NAME

		inline static const std::string EventName{ "TestEvent1" };
	};


	struct TestEvent2 : public TestEvent
	{
		TestEvent2() : TestEvent(2) { }

		TestEvent2(int i) : TestEvent(i) { }

		GET_EVENT_NAME

		inline static const std::string EventName{ "TestEvent2" };
	};



	class TestEventSystem : public TestBase
	{
	public:
		auto GenerateEvents() -> void;
		auto GenerateListeners() -> void;



		auto RunTest() -> void override;


	private:
		system::EventSystem event_sys;
	};

} //namespace gargantua::test