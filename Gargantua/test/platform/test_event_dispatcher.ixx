export module gargantua.test.test_event_dispatcher;

import gargantua.platform;

namespace gargantua::test
{
	using namespace gargantua::platform;

	export 
	class TestEventDispatcher
	{
	public:
		auto RunTest() -> void
		{
			auto& ps = platform::PlatformSystem::Instance();
			ps.Startup(720, 480, "Test");

			auto& dispatcher = platform::PlatformEventDispatcher::Instance();

			bool should_close = false;

			dispatcher.RegisterListener<WindowCloseEvent>([&](const WindowCloseEvent& e)
				{
					should_close = e.is_closed;
				});


			while (!should_close)
			{
				ps.Run();
			}
		}
	};

} // namespace gargantua::test

