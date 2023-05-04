import <iostream>;


import gargantua.core.engine;
import gargantua.app.application;

import sandbox.test_app;

using namespace gargantua;

int main()
{
	core::Engine engine{ 720, 480, "test" };
	
	engine.CreateApplication<TestApp>();

	engine.Run();


	return 0;
}