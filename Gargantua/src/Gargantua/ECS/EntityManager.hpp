#pragma once
/*
Gargantua/ECS/EntityManager.hpp


PURPOSE: Generate entities.

CLASSES:
	EntityManager: generate entities (ids) using a generator passed by the user.

DESCRIPTION:
	The EntityManager is responsible to create and destroy entities. To make it more flexible, a custom generator can be 
	passed as template parameter. The generate must generate only positive numbers and be a MonotonicGenerator.
	To keep track of entities in use, a std::set is used. For now O(log(n)) it's okay for all methods.


TODO:
	For now i will not use a queue to keep track of reusable entities. I prefer to do things in a simple way.
	For reusing the entities i could use a queue to keep track of destroyed entitites.
	For a faster on entities i could use an hashmap instaed of a red-black tree.


USAGE:
	EntityManager<SequentialNumberGenerator> mng;

	auto entity = mng.Create();

	...

	if (mng.InUse(entity)) 
	{
		...
	}

	...

	mng.Destroy(entity);
	mng.Destroy(entity); //do nothing0

*/

#include "Gargantua/Types.hpp"

#include "Gargantua/ECS/Types.hpp"

#include "Gargantua/Concepts/Generator.hpp"

#include <queue>
#include <set>
#include <ranges>


namespace Gargantua
{
	namespace ECS
	{
		template <template <class> typename TGenerator> 
		requires Concepts::Generator<TGenerator<Entity>>
		class EntityManager
		{
		public:
			Entity Create()
			{
				Entity id = gen.Get();
				entities_in_use.emplace(id);

				return id;
			}

			/*
			If entities is not in use (is not "alive"), do nothing.
			*/
			void Destroy(Entity e)
			{
				if (auto it = entities_in_use.find(e); it != entities_in_use.end())
				{
					entities_in_use.erase(it);
				}
			}


			
			bool InUse(Entity e) const noexcept
			{
				return entities_in_use.contains(e);
			}


			auto GetEntitiesView()
			{
				return std::views::all(entities_in_use);
			}


		private:
			TGenerator<Entity> gen;
			//std::queue<Entity> available_entities;
			std::set<Entity> entities_in_use;
		};
	} //namespace ECS
} //namespace Gargantua