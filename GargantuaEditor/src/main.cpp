
import gargantua.core.engine;
import gargantua.editor.editor;

//import gargantua.test.parallel.test_task_system;

using namespace gargantua;

int main()
{
	core::Engine engine{ 1280, 720, "test" };

	engine.CreateApplication<editor::Editor>();
	engine.Run();

	//test::TestTaskSystem t;

	//t.RunTest();

	return 0;
}