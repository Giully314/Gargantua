/*
gargantua/ecs/component_manager.ixx


*/

export module gargantua.ecs.component_manager;

import <concepts>;
import <unordered_map>;
import <typeinfo>;
import <typeindex>;

import gargantua.types;
import gargantua.ecs.ecs_types;
import gargantua.ecs.component_storage;


export namespace gargantua::ecs
{
	class ComponentManager
	{
	public:
		
		template <std::semiregular T>
		auto RegisterComponent() -> void
		{
			if (!components.contains(std::type_index(typeid(T)))) [[likely]]
			{
				components[std::type_index(typeid(T))] = CreateUniqueRes<ComponentStorage<T>>();
			}
		}


		template <std::semiregular T>
		auto UnregisterComponent() -> void
		{
			if (components.contains(std::type_index(typeid(T)))) [[likely]]
			{
				components.erase(std::type_index(typeid(T)));
			}
		}


		template <typename T>
		auto GetComponentStorage() -> ComponentStorage<T>&
		{
			return static_cast<ComponentStorage<T>&>(*components.at(std::type_index(typeid(T))));
		}



	private:
		std::unordered_map<std::type_index, UniqueRes<ComponentStorageHandler>> components;
	};

} //namespace gargantua::ecs
