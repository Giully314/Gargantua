#pragma once
/*
Gargantua/ECS/EntityManager.hpp


PURPOSE: Generate entities.

CLASSES:
	EntityManager: generate entities (ids) using a generator passed by the user.

DESCRIPTION:
	The EntityManager is responsible to create and destroy entities. For make it more flexible, a custom generator can be passed
	by template parameter. The generate must generate only positive numbers and be a MonotonicGenerator.

USAGE:
	EntityManager<SequentialNumberGenerator> mng;

	auto entity = mng.Create();

	...
	...

	mng.Destroy(entity);

*/

#include "Gargantua/Types.hpp"

#include "Gargantua/ECS/Types.hpp"

#include "Gargantua/Concepts/Generator.hpp"

#include <queue>


namespace Gargantua
{
	namespace ECS
	{
		template <template <class> typename TGenerator> 
		requires Concepts::Generator<TGenerator<Entity>>
		class EntityManager
		{
		public:

			inline Entity Create()
			{
				if (available_entities.empty())
				{
					Fill(512);
				}


				natural_t id = available_entities.front();
				available_entities.pop();

				return id;
			}


			inline void Destroy(Entity e)
			{
				available_entities.push(e);
			}

			
		private:
			void Fill(const natural_t n)
			{
				//check if the generator is at the maximum value...
				//or assume that after a complete loop, the entities are safe to be reused.
				for (natural_t i = 0; i < n; ++i)
				{
					available_entities.push(gen.Get());
				}
			}

		private:
			TGenerator<Entity> gen;
			std::queue<Entity> available_entities;
		};
	} //namespace ECS
} //namespace Gargantua