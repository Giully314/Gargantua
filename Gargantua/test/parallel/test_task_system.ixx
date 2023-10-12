/*
* test/parallel/test_task_system.ixx
* 
* TODO:
*	- this test is incomplete.
*/

export module gargantua.test.parallel.test_task_system;

import gargantua.test.base_test;
import gargantua.parallel.parallel;

import <thread>;
import <chrono>;

namespace gargantua::test
{
	export
	class TestTaskSystem : public BaseTest
	{
	public:
		auto RunTest() -> void override
		{
			using namespace std::chrono_literals;

			mutex_logger.Info("START");
			parallel::TaskSystem& ts = parallel::TaskSystem::Instance();

			for (int i = 0; i < 10; ++i)
			{
				ts.Register([&, i]()
					{
						mutex_logger.Info("Here {}", i);
					});
			}

			std::this_thread::sleep_for(1s);
		}
	};
} // namespace gargantua::test