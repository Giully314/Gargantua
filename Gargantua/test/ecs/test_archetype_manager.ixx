///*
//
//*/
//
//export module gargantua.test.ecs.test_archetype_manager;
//
//import <unordered_map>;
//
//import gargantua.test.test_base;
//import gargantua.test.ecs.components;
//
//import gargantua.types;
//import gargantua.ecs.ecs;
//
//
//export namespace gargantua::test
//{
//
//	class TestArchetype : public TestBase
//	{
//	public:
//		auto RunTest() -> void override
//		{
//			arch_mng.RegisterArchetype<Position, Velocity>();
//
//
//		}
//
//	private:
//		ecs::EntityManager ent_mng;
//		ecs::ArchetypeManager arch_mng;
//	};
//
//} //namespace gargantua::test