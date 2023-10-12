export module gargantua.test.ecs.test_ecs_system;

import gargantua.test.base_test;
import gargantua.ecs;
import gargantua.test.ecs.components;

namespace gargantua::test
{
	using namespace gargantua::ecs;
	
	export 
	class TestECSSystem : public BaseTest
	{
	public:
		auto RunTest() -> void override
		{
			constexpr u32 N = 100;
			for (auto i = 0; i < N; ++i)
			{
				entities.push_back(ecs.Create());
			}

			ecs.Register<Position>();
			ecs.Register<Velocity>();
			ecs.Register<Acceleration>();

			float x = 1.0f;
			auto i = 0;
			for (auto e : entities)
			{
				++i;
				if (i % 2 == 0)
				{
					continue;
				}
				ecs.Emplace<Position>(e);
				ecs.Emplace<Velocity>(e, x, x + 1.0f);
				ecs.Emplace<Acceleration>(e);
				x += 2.0f;
			}

			/*ecs.ForEach<Position, Velocity>([](Position& p, Velocity& v)
				{
					p.p += { 1.0f, 1.0f};
				});*/
			//auto group = ecs.Group<Position, Velocity>();
			ecs.ForEach<Position, Velocity>([](Position& p, Velocity& v)
				{
					p.p += v.v * 0.1f;
				});

			
			for (auto e : entities)
			{
				PrintEntity(e);
				ecs.Destroy(e);
			}

		}

	private:
		auto PrintEntity(entity_t e) -> void
		{
			if (!ecs.Has<Position>(e)) return;

			auto& p = ecs.Get<Position>(e);
			auto& v = ecs.Get<Velocity>(e);
			auto& a = ecs.Get<Acceleration>(e);

			logger.Debug("Entity {}", e);
			logger.Debug("Position:	    {}", p.p.ToString());
			logger.Debug("Velocity:	    {}", v.v.ToString());
			logger.Debug("Acceleration: {}\n", a.a.ToString());
		}

	private:
		ECSSystem ecs;
		std::vector<entity_t> entities;
	};
} // namespace gargantua::test
