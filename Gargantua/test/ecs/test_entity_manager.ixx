/*
test/ecs/test_entity_manager.ixx
*/

export module gargantua.test.ecs.test_entity_manager;

import <vector>;

import gargantua.test.test_base;

import gargantua.ecs.ecs;


export namespace gargantua::test
{
	class TestEntityManager : public TestBase
	{
	public:

		auto RunTest() -> void override;

	private:
		ecs::EntityManager mng;
		std::vector<ecs::entity_t> entities;


		auto PrintEntities() -> void;
		auto PrintEntitiesBinary() -> void;
	};
} //namespace gargantua::test