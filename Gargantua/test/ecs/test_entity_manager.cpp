/*
test/ecs/test_entity_manager.cpp
*/

module;

#include <bitset>

module gargantua.test.ecs.test_entity_manager;



namespace gargantua::test
{

	auto TestEntityManager::RunTest() -> void
	{
		logger.Debug("Start Run test");

		constexpr unsigned int N = 8;
		entities.reserve(N);
		for (unsigned int i = 0; i < N; ++i)
		{
			entities.emplace_back(mng.Create());
		}

		PrintEntities();
		PrintEntitiesBinary();

		logger.Debug("Destroy entities and recreate them");

		for (auto e : entities)
		{
			mng.Destroy(e);
		}

		entities.clear();

		for (int i = 0; i < N; ++i)
		{
			entities.push_back(mng.Create());
		}

		PrintEntities();
		PrintEntitiesBinary();


		logger.Debug("Destroy entities and recreate them");

		for (auto e : entities)
		{
			mng.Destroy(e);
		}

		entities.clear();

		for (int i = 0; i < N; ++i)
		{
			entities.emplace_back(mng.Create());
		}

		PrintEntities();
		PrintEntitiesBinary();

		logger.Debug("End of test");
	}


	auto TestEntityManager::PrintEntities() -> void
	{
		const auto n = entities.size();
		for (auto i = 0; i < n; ++i)
		{
			logger.Debug("Entity: {}", entities[i]);
			/*logger.Debug("Entity: {},  id: {},  gen: {}", entities[i], 
				ecs::EntityManipulation::ExtractID(entities[i]), ecs::EntityManipulation::ExtractGeneration(entities[i]));*/
		}
	}


	auto TestEntityManager::PrintEntitiesBinary() -> void
	{
		const auto n = entities.size();
		for (auto i = 0; i < n; ++i)
		{
			logger.Debug("Entity id in binary: {}", std::bitset<32>(entities[i]).to_string());
		}
	}

} //namespace gargantua::test