
export module gargantua.test.ecs.test_component_manager;

import gargantua.test.test_base;
import gargantua.test.ecs.components;

import gargantua.ecs.component_manager;
import gargantua.ecs.component_storage;

export namespace gargantua::test
{
	class TestComponentManager : public TestBase
	{
	public:


		auto RunTest() -> void override
		{
			m.RegisterComponent<Position>();
			auto s = m.GetComponentStorage<Position>();
		}

	private:
		ecs::ComponentManager m;
	};
} //namespace gargantua::test