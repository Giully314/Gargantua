//export module gargantua.test.test_event_dispatcher;
//
//import gargantua.platform.platform;
//import gargantua.platform.platform_system;
//
//namespace gargantua::test
//{
//	using namespace gargantua::platform;
//
//	export 
//	class TestEventDispatcher
//	{
//	public:
//		auto RunTest() -> void
//		{
//			window.SetEventDispatcher(&dispatcher);
//			window.RegisterEventsCallbacks();
//
//
//			bool should_close = false;
//
//			dispatcher.RegisterListener<WindowCloseEvent>([&](WindowCloseEvent& e)
//				{
//					should_close = e.is_closed;
//				});
//
//
//			while (!should_close)
//			{
//				window.Update();
//			}
//		}
//
//	private:
//		InitGLFW init;
//		PlatformEventDispatcher dispatcher;
//		Window window{720, 480, "event dispatcher test"};
//		
//	};
//
//} // namespace gargantua::test
//
