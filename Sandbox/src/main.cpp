
import gargantua;
import sandobox.testapp;

using namespace gargantua;

int main()
{
	core::Engine engine{ 1080, 720, "TestEngine" };

	engine.CreateApplication<TestApplication>();
	engine.Run();

	return 0;
}