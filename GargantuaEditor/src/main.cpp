
import gargantua.core.engine;
import gargantua.editor.editor;

using namespace gargantua;

int main()
{
	core::Engine engine{ 1080, 720, "test" };

	engine.CreateApplication<editor::Editor>();
	engine.Run();

	return 0;
}