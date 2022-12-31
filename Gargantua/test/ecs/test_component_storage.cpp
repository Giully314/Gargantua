/*
test/ecs/test_component_storage.cpp
*/
module gargantua.test.ecs.test_component_storage;


namespace gargantua::test
{
	auto TestComponentStorage::RunTest() -> void
	{
		ecs::entity_t e0 = 0;
		ecs::entity_t e1 = 1;
		ecs::entity_t e2 = 2;
		ecs::entity_t e3 = 3;
		ecs::entity_t e4 = 4;
		

		RegisterComponent<Position>();
		RegisterComponent<Velocity>();
		RegisterComponent<Acceleration>();

		auto& p_storage = GetStorage<Position>();

		auto& p1 = p_storage.Emplace(e1);
		p1.p = { 1.0f, 1.0f };

		auto& p2 = p_storage.Emplace(e2, 2.0f, 2.0f);

		auto& p3 = p_storage.Emplace(e3, 3.0f, 3.0f);
		
		auto& p4 = p_storage.Emplace(e4, 4.0f, 4.0f);

		logger.Debug("index of e1 {}", p_storage.IndexOf(e1));

		p_storage.Erase(e1);


		p4 = p_storage[e4];
		logger.Debug("{}", p4.p.ToString());
		p_storage.Erase(e4);
		p3 = p_storage[e3];
		logger.Debug("{}", p3.p.ToString());
	}

} //namespace gargantua::test