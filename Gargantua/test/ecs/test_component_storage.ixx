/*
test/ecs/test_component_storage.ixx
*/

export module gargantua.test.ecs.test_component_storage;

import <vector>;
import <unordered_map>;
import <typeindex>;
import <typeinfo>;
import <memory>;

import gargantua.test.test_base;
import gargantua.test.ecs.components;

import gargantua.ecs.component_storage;
import gargantua.ecs.ecs_types;



export namespace gargantua::test
{
	class TestComponentStorage : public TestBase
	{
	public:

		auto RunTest() -> void override;

	private:
		std::unordered_map<std::type_index, std::unique_ptr<ecs::ComponentStorageHandler>> m;
		ecs::ComponentStorage<Position> storage;
		std::vector<ecs::entity_t> entities;

	private:
		template <typename T>
		auto RegisterComponent() -> void
		{
			m[std::type_index(typeid(Position))] = std::make_unique<ecs::ComponentStorage<T>>();
		}

		template <typename T>
		auto GetStorage() -> ecs::ComponentStorage<T>&
		{
			return static_cast<ecs::ComponentStorage<T>&>(*m[std::type_index(typeid(Position))]);
		}

	};
} //namespace gargantua::test