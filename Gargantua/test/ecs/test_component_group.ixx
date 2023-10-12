export module gargantua.test.ecs.test_component_group;

import gargantua.test.base_test;
import gargantua.test.ecs.components;
import gargantua.ecs;
import <vector>;

namespace gargantua::test
{
	using namespace gargantua::ecs;
	export 
	class TestComponentGroup : public BaseTest
	{
	public:

		auto RunTest() -> void override
		{
			comp_mng.Register<Position>();
			comp_mng.Register<Velocity>();
			comp_mng.Register<Acceleration>();

			for (auto i = 0; i < 10; ++i)
			{
				entities.push_back(ent_mng.Create());
			}

			/*
			* The for each works, however the way id are passed and then stored is broken. We store the entity and not 
			* the id. That's a problem because we
			*/

			for (auto i = 0; i < 5; ++i)
			{
				comp_mng.Emplace<Position>(entities[i]);
				comp_mng.Emplace<Velocity>(entities[i]);
				comp_mng.Emplace<Acceleration>(entities[i]);
				/*float x = i;
				comp_mng.Emplace<Position>(entities[i], x + 1, x + 1);
				comp_mng.Emplace<Velocity>(entities[i], x + 1, x + 1);
				comp_mng.Emplace<Acceleration>(entities[i], x, x);*/
			}

			for (auto i = 5u; i < entities.size(); ++i)
			{
				float x = static_cast<float>(i);
				comp_mng.Emplace<Position>(entities[i], x, x);
				comp_mng.Emplace<Velocity>(entities[i], x, x);
				comp_mng.Emplace<Acceleration>(entities[i], x, x);
			}
			
			auto& c1 = comp_mng.GetComponentStorage<Position>();
			auto& c2 = comp_mng.GetComponentStorage<Velocity>();

			logger.Debug("SIZE {} {}", c1.Size(), c2.Size());

			auto group = comp_mng.Group<Position, Velocity>();
			group.ForEach([&](Position& p, Velocity& v)
				{
					logger.Debug("Inside");
					logger.Debug("{} {}\n", p.p.ToString(), v.v.ToString());
					p.p += v.v * 2;
				});

			for (auto e : entities)
			{
				PrintEntity(e);
			}
		}

	private:
		auto PrintEntity(entity_t e) -> void
		{
			auto& p = comp_mng.Get<Position>(e);
			auto& v = comp_mng.Get<Velocity>(e);
			auto& a = comp_mng.Get<Acceleration>(e);

			logger.Debug("Entity {}", e);
			logger.Debug("Position:	    {}", p.p.ToString());
			logger.Debug("Velocity:	    {}", v.v.ToString());
			logger.Debug("Acceleration: {}\n", a.a.ToString());
		}

	private:
		ComponentManager comp_mng;
		EntityManager ent_mng;
		std::vector<entity_t> entities;
	};
} // namespace gargantua::test
