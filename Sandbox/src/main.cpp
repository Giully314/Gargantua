#include <Gargantua/Engine.hpp>
#include "App.hpp"



int main()
{

	Gargantua::Engine e{ []() {return new Sandbox::App{}; }, 1280, 720 };
	e.Run();

	return 0;
}