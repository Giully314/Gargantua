/*
gargantua/system/ecs_system.ixx

PURPOSE:

CLASSES:

DESCRIPTION:

*/

export module gargantua.system.ecs_system;

import <concepts>;
import <tuple>;

import gargantua.ecs.ecs;

export namespace gargantua::system
{
	class Entity
	{
	public:
		friend class ECSSystem;

		Entity(ecs::entity_t entity_id, ecs::ComponentManager& comp_mng) : e(entity_id), 
			component_mng(comp_mng)
		{

		}


		template <std::semiregular TComponent, typename ...Args>
			requires std::constructible_from<TComponent, Args...>
		auto Emplace(Args&& ...args) -> TComponent&
		{
			auto& storage = component_mng.GetComponentStorage<TComponent>();
			return storage.Emplace(e, std::forward<Args>(args)...);
		}


		template <std::semiregular TComponent>
		auto Erase() -> void
		{
			auto& storage = component_mng.GetComponentStorage<TComponent>();
			storage.Erase(e);
		}


		auto GetID() const noexcept -> ecs::entity_t
		{
			return e;
		}

	private:
		ecs::entity_t e;
		ecs::ComponentManager& component_mng;
	};


	class ECSSystem
	{
	public:

		auto CreateEntity() -> Entity
		{
			return { entity_mng.CreateEntity(), component_mng };
		}
		
		auto DestroyEntity(Entity& e) -> void;

		/*
		* Light version of destroying an entity.
		* It doesn't check all the components associated to the entity.
		* Call this if you are sure that the entity has no component registered.
		* Complexity: O(1).
		*/
		auto ReleaseEntity(Entity& e) -> void
		{
			entity_mng.DestroyEntity(e.GetID());
			e.e = ecs::NullEntity;
		}


		template <std::semiregular TComponent>
		auto RegisterComponentType() -> void
		{
			component_mng.RegisterComponent<TComponent>();
		}


		template <std::semiregular TComponent>
		auto UnregisterComponent() -> void
		{
			component_mng.UnregisterComponent<TComponent>();
		}


		/*
		* Apply f to each entity that has the components.
		* Note that the arguments of f must be in the same order as the components
		* passed as template parameters.
		*/
		template <typename F, std::semiregular ...TComponents>
		auto ForEach(F&& f) -> void
		{
			/*auto comps = std::tie(component_mng.GetComponentStorage<TComponents>()...);
			
			int min = std::get<0>(comps).Size();
			auto& cs = std::apply(
				[] (const auto&... t) 
			{
				
			};
				,comps);*/
		}


	private:
		ecs::EntityManager entity_mng;
		ecs::ComponentManager component_mng;
	};
} //namespace gargantua::system