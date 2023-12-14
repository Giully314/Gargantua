export module gargantuatest.ecs.test_component_manager;

import <cassert>;

import gargantua;

import gargantuatest.testbase;
import gargantuatest.ecs.test_components;


namespace gargantuatest
{
	export class TestComponentManager : public TestBase
	{
	public:
		auto RunTest() -> void
		{
			using namespace gargantua::ecs;
			EntityManager emng;
			ComponentManager cmng;

			{
				auto l = ConsoleLogTester("TestComponentManager");
				
				// Register components
				cmng.Register<Position>();
				cmng.Register<Velocity>();

				auto e1 = emng.Create();
				auto e2 = emng.Create();
			
				auto& p1 = cmng.Emplace<Position>(e1);
				auto& v1 = cmng.Emplace<Velocity>(e1, 4);
				p1.x += v1.x * 3;

				auto& p2 = cmng.Emplace<Position>(e2);
				auto& v2 = cmng.Emplace<Velocity>(e2, 5);
				p2.x += v2.x * 5;
				


				logger.Debug("e1 position {}", cmng.Get<Position>(e1).x);
				logger.Debug("e2 position {}", cmng.Get<Position>(e2).x);
				assert(("Position for e1 is not correct", cmng.Get<Position>(e1).x == 12));
				assert(("Position for e2 is not correct", cmng.Get<Position>(e2).x == 25));



				auto g = cmng.Group<Position, Velocity>();
				g.ForEach([](Position& p, const Velocity& v)
					{
						p.x += v.x;
					});

				logger.Debug("e1 position after for each {}", cmng.Get<Position>(e1).x);
				logger.Debug("e2 position after for each {}", cmng.Get<Position>(e2).x);
				assert(("Position for e1 is not correct", cmng.Get<Position>(e1).x == 16));
				assert(("Position for e2 is not correct", cmng.Get<Position>(e2).x == 30));
			}
		}
	};
} // namespace gargantuatest
