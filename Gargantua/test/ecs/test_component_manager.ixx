
export module gargantua.test.ecs.test_component_manager;

import gargantua.test.test_base;
import gargantua.test.ecs.components;

import gargantua.ecs.ecs;

export namespace gargantua::test
{
	class TestComponentManager : public TestBase
	{
	public:


		auto RunTest() -> void override
		{
			m.RegisterComponent<Position>();
			m.RegisterComponent<Velocity>();
			m.RegisterComponent<Acceleration>();

			auto& ps = m.GetComponentStorage<Position>();
			auto& vs = m.GetComponentStorage<Velocity>();
			auto& as = m.GetComponentStorage<Acceleration>();
		}

	private:
		ecs::ComponentManager m;
	};
} //namespace gargantua::test