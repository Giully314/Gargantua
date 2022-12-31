/*
gargantua/ecs/component_manager.ixx

PURPOSE:

CLASSES:

DESCRIPTION:



*/

export module gargantua.ecs.ecs:component_manager;

import <concepts>;
import <unordered_map>;
import <typeinfo>;
import <typeindex>;

import gargantua.types;
import :component_storage;

export namespace gargantua::ecs
{
	class ComponentManager
	{
	public:

		/*
		* 
		*/
		template <std::semiregular TComponent>
		auto RegisterComponent() -> void
		{
			auto i = std::type_index(typeid(TComponent));
			if (!components.contains(i)) [[likely]]
			{
				components[i] = CreateUniqueRes<ComponentStorage<TComponent>>();
			}
		}


		/*
		* 
		*/
		template <std::semiregular TComponent>
		auto UnregisterComponent() -> void
		{
			auto i = std::type_index(typeid(TComponent));
			if (components.contains(i)) [[likely]]
			{
				components.erase(i);
			}
		}

		/*
		* 
		*/
		template <std::semiregular TComponent>
		auto GetComponentStorage() -> ComponentStorage<TComponent>&
		{
			return static_cast<ComponentStorage<TComponent>&>(*components.at(std::type_index(typeid(TComponent))));
		}

	private:
		std::unordered_map<std::type_index, UniqueRes<ComponentStorageHandler>> components;
	};
} //namespace gargantua::ecs
