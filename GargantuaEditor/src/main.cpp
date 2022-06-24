#include <Gargantua/Engine.hpp>

#include "GargantuaEditor.hpp"


int main()
{

	//Gargantua::Engine e{ []() {return new Sandbox::App{}; }, 1280, 720 };
	Gargantua::Engine e{ &Gargantua::Editor::CreateGargantuaEditorApplication, 1280, 720 };
	e.Run();

	return 0;
}