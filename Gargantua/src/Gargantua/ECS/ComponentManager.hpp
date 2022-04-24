#pragma once
/*
Gargantua/ECS/ComponentManager.hpp


PURPOSE: Manages 1 type of component.

CLASSES:
	ComponentManager: manager for a component.

DESCRIPTION:
	This manager handles one component type in a contigous array (std::vector). Entities can be registered or 
	unregistered to get or remove the component. Both operations are O(1) (in avarage cases) and to allow this, 
	extra memory for 2 maps is used. 
	(For more informations, check https://en.cppreference.com/w/cpp/container/unordered_map for complexity times)
	The order of insertion is not guaranteed because Unregister swap elements to get O(1) instaed of O(n)
	for removing a component.

USAGE:
	ComponentManager<PositionComponent> mng;
	auto& pos_comp = mng.Register(entity, position_vec, rotation_vec);
	
	...

	auto& another_ref = mng.Get(entity); //entity must be registered.

	...

	mng.Unregister(entity);

TODO:
	this is a temporary solution. Consider other ways to implement a component manager with pro/cons.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/ECS/Types.hpp"

#include "Gargantua/Core/EngineLogger.hpp"

#include <concepts>

#include <utility>

#include <vector>
#include <unordered_map>

namespace Gargantua
{
	namespace ECS
	{
		template <typename T> 
		requires std::default_initializable<T> && std::movable<T>
		class ComponentManager
		{
		public:
			using ValueType = T;


			/*
			If the entity is already registered, return the component associated.
			*/
			template <typename ...Args>
				requires std::constructible_from<T, Args...>
			ValueType& Register(Entity e, Args&& ...args)
			{
				//Check if the entity is already registered and return the component in case.
				if (auto it = ent_to_idx.find(e); it != ent_to_idx.end())
				{
					return components[it->second];
				}

				//Construct the component and set the 2 maps with the respective info.

				components.emplace_back(std::forward<Args>(args)...);

				natural_t idx = static_cast<natural_t>(components.size() - 1);

				ent_to_idx.insert({ e, idx });
				idx_to_ent.insert({ idx, e });

				//GRG_CORE_INFO("Entity {} idx {}", e, idx);

				return components.back();
			}
		

			/*
			If the entity is not registered, do nothing.
			*/
			void Unregister(Entity e)
			{
				//Check if the entity is registered for removing the component.
				if (auto it = ent_to_idx.find(e); it != ent_to_idx.end())
				{
					//If there is only one component or the position is already at the end just remove it
					if (components.size() == 1 || it->second == (components.size() - 1))
					{
						//GRG_CORE_INFO("Last position");
						idx_to_ent.erase(it->second);
						ent_to_idx.erase(e);
						components.pop_back();
						return;
					}


					/*
					Get the idx of the last element, 
					extract the node associated to this last element from from idx_to_ent to change info later,
					swap the last element with the element to be removed 
					erase the info of the entity argument
					update the information of the swapped component
					erase the last element. 
					In this way the operation is O(1) (in avarage) instaed of O(n).
					*/

					auto ent_del_node = ent_to_idx.extract(it);
					auto idx_del_node = idx_to_ent.extract(ent_del_node.mapped());

					natural_t last_ent_idx = static_cast<natural_t>(components.size() - 1);
					auto node = idx_to_ent.extract(last_ent_idx);

					std::swap(components[last_ent_idx], components[ent_del_node.mapped()]);
					

					ent_to_idx[node.mapped()] = ent_del_node.mapped();
					node.key() = ent_del_node.mapped();

					idx_to_ent.insert(std::move(node));

					components.pop_back();
				}
			}


			/*
			Undefined behavior or exception if the entity is not registered.
			*/
			ValueType& Get(Entity e)
			{
				return components[ent_to_idx[e]];
			}


			bool HasComponent(Entity e)
			{
				return ent_to_idx.contains(e);
			}


		private:
			//I prefer to use 2 maps for fast lookup in the Unregister function.
			std::unordered_map<Entity, natural_t> ent_to_idx;
			std::unordered_map<natural_t, Entity> idx_to_ent;

			std::vector<ValueType> components; 
		};
	} //namespace ECS 
} //namespace Gargantua