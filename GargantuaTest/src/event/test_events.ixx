export module gargantuatest.event.test_events;

import <string>;

import gargantua.event;

using namespace gargantua::event;

export namespace gargantuatest
{

	struct TestEvent1 : BaseEvent
	{
		std::string s{ "TestEvent1" };
	};


	struct TestEvent2 : BaseEvent
	{
		std::string s{ "TestEvent2" };
	};

	struct TestEvent3 : BaseEvent
	{
		std::string s{ "TestEvent3" };
	};


	struct TestEvent4 : BaseEvent
	{
		TestEvent4(int x_) : x(x_)
		{

		}

		int x{ 0 };
		std::string s{ "TestEvent4" };
	};

} // namespace gargantuatest