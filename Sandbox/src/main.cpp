import gargantua.engine.engine;

import sandbox.app;


import gargantua.test.ecs.test_component_manager;

int main()
{

	/*gargantua::engine::Engine e{ []() {return new sandbox::App{}; }, 1280, 720 };
	e.Run();*/

	gargantua::test::TestComponentManager test;

	test.RunTest();

	return 0;
}