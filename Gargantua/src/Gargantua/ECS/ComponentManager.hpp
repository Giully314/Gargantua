#pragma once
/*
Gargantua/ECS/ComponentManager.hpp


PURPOSE: Manages multiple component storage.

CLASSES:
	ComponentManager: manager for all the component types.


DESCRIPTION:
	Manager for the components passed at compile time through a TypeList. This class manages the "glue" code to get
	all the different ComponentStorage works with a unified interface. All the functions address the correct 
	ComponentStorage based on the type TComponent and forward the call to it.



USAGE:
	using Components = TypeList<TransformComponent, SpriteComponent>;
	ComponentManager<Components> mng;

	mng.Register<TransformComponent>(entity, position_vec);
	mng.Register<SpriteComponent>(entity, texture);
	
	...

	auto& component = mng.Get<TransformComponent>(entity); //entity must be registered.

	...

	mng.Unregister<SpriteComponent>(entity);


	
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ComponentStorage.hpp"

#include "Gargantua/Core/EngineLogger.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include <concepts>
#include <utility>
#include <tuple>


namespace Gargantua
{
	namespace ECS
	{
		template <typename TComponents>
		class ComponentManager
		{
		public:
			using TypeListOfComponents = TComponents;


			template <typename TComponent, typename ...Args>
				requires std::constructible_from<TComponent, Args...> && 
					MPL::IsPresentV<TypeListOfComponents, TComponent>
			TComponent& Register(Entity e, Args&& ...args)
			{
				ComponentStorage<TComponent>& comp_storage = GetComponentStorage<TComponent>();
				return comp_storage.Register(e, std::forward<Args>(args)...);
			}


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			void Unregister(Entity e)
			{
				ComponentStorage<TComponent>& comp_storage = GetComponentStorage<TComponent>();
				comp_storage.Unregister(e);
			}


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			TComponent& Get(Entity e)
			{
				ComponentStorage<TComponent>& comp_storage = GetComponentStorage<TComponent>();
				return comp_storage.Get(e);
			}


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			const TComponent& Get(Entity e) const
			{
				ComponentStorage<TComponent>& comp_storage = GetComponentStorage<TComponent>();
				return comp_storage.Get(e);
			}


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			bool Has(Entity e) const
			{
				ComponentStorage<TComponent>& comp_storage = GetComponentStorage<TComponent>();
				return comp_storage.Has(e);
			}
		

		private:
			template <typename T>
			struct ToComponentStorage
			{
				using Type = ComponentStorage<T>;
			};

			using ComponentsStorageType = MPL::RebindT<MPL::TransformT<TComponents, ToComponentStorage>, std::tuple>;


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			ComponentStorage<TComponent>& GetComponentStorage()
			{
				return std::get<ComponentStorage<TComponent>>(components);
			}

		private:
			ComponentsStorageType components;
		};
	} //namespace ECS 
} //namespace Gargantua