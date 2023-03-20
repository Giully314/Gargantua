import <iostream>;

import gargantua.platform.platform_manager;
import gargantua.platform.window;

import gargantua.core.engine;

using namespace gargantua;

int main()
{
	core::Engine engine;

	engine.Run();

	/*try
	{
		gargantua::platform::Window window{ 720, 480, "Test" };
		while (true)
		{
			window.Update();
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}*/


	return 0;
}