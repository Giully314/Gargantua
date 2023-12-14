/*
* test/parallel/test_task_system.ixx
* 
* TODO:
*	- this test is incomplete.
*/

export module gargantuatest.parallel.test_task_system;

import gargantuatest.testbase;
import gargantua.parallel;

import <thread>;
import <chrono>;

namespace gargantuatest
{
	export class TestTaskSystem : public TestBase
	{
	public:
		auto RunTest() -> void 
		{
			using namespace gargantua;
			using namespace std::chrono_literals;

			//mutex_logger.Debug("START");
			auto& ts = parallel::TaskSystem::Instance();
			ts.Startup();
			{
				auto l = MutexConsoleLogTester("TaskSystem");
				for (int i = 0; i < 10; ++i)
				{
					ts.Register([&, i]()
						{
							mutex_logger.Debug("Here {}", i);
						});
				}

				std::this_thread::sleep_for(1s);
			}
		}
	};
} // namespace gargantuatest