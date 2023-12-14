
import gargantuatest.event.test_event_dispatcher;
import gargantuatest.math.test_vector;
import gargantuatest.parallel.test_task_system;
import gargantuatest.ecs.test_entity_manager;
import gargantuatest.ecs.test_component_manager;

int main()
{
	using namespace gargantuatest;

	EventDispatcherTest event_dispatcher_test;
	event_dispatcher_test.RunTest();

	TestVector test_vector;
	test_vector.RunTest();

	TestTaskSystem test_task_system;
	test_task_system.RunTest();

	TestEntityManager test_entity_manager;
	test_entity_manager.RunTest();

	TestComponentManager test_component_manager;
	test_component_manager.RunTest();

	return 0;
}