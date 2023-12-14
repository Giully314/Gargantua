export module gargantuatest.ecs.test_entity_manager;

import <cassert>;

import gargantua;

import gargantuatest.testbase;


namespace gargantuatest
{
	export class TestEntityManager : public TestBase
	{
	public:
		void RunTest()
		{
			using namespace gargantua::ecs;
			EntityManager emng;

			{
				auto l = ConsoleLogTester("TestEntityManager");
				auto e1 = emng.Create();
			
				assert(("First entity generated must be 0", e1 == 0));
			
				emng.Destroy(e1);
				e1 = emng.Create();
				assert(("Entity 0 recycled must be (1<<26)", e1 == (1 << 26)));
			}
		}
	};

} // namespace gargantuatest