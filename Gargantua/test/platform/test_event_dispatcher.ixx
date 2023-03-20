export module gargantua.test.test_event_dispatcher;

import gargantua.platform.event_dispatcher;
import gargantua.platform.platform_events;

namespace gargantua::test
{
	using namespace gargantua::platform;

	export 
	class TestEventDispatcher
	{
	public:
		auto RunTest() -> void
		{
			
		}

	private:
		PlatformEventDispatcher dispacther;
	};

} // namespace gargantua::test

