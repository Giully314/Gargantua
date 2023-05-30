/*
* gargantua/ecs/entity_manager.ixx
* 
* PURPOSE: Manage id for the ecs.
* 
* CLASSES:
*	EntityManager: Create and destroy id for entities.
* 
* DESCRIPTION:
*	Create, destroy and check if an entity is alive. All the operations are done in constant time.
* 
* 
* TODO:
*	- Add checks for generation part overflow when destroy an entity? Or let it round to 0?	
* 
* USAGE:
*	EntityManager mng;
*	auto e1 = mng.Create();
*	
*	// do my operations with e1.
*	...
* 
*	// Destroy the entity when i'm done.
*	mng.Destroy(e1);
* 
*	if (mng.IsAlive(e1))  // return false.
*		...
* 
*/


export module gargantua.ecs.entity_manager;

import <vector>;

import gargantua.types;
import gargantua.ecs.entity;
import gargantua.generator.sequential_generator;

namespace gargantua::ecs
{
	export
	class EntityManager
	{
	public:
		EntityManager() : available(0), next(0) 
		{
			
		}


		/*
		* Creates an id and register it to the living entities.
		* Complexity: O(1).
		*/
		[[nodiscard("Entity's id must not be ignored for id leak")]]
		auto Create() -> entity_t;


		/*
		* Destroys an id and put its id in a container for reuse.
		* Precondition: The id must be valid.
		* Complexity: O(1).
		*/
		auto Destroy(entity_t id) -> void;


		/*
		* Check if an entity is currently used. The check is based on the generation part.
		* Precondition: Entity must be valid.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		auto IsAlive(entity_t e) -> bool
		{
			return entities[EntityManipulation::Entity(e)] == e;
		}


	private:
		generator::SequentialGenerator<id_t> g;
		std::vector<id_t> entities;
		u32 available;

		//contains the entity (that is the index in the entities) that can be recycled.
		id_t next;
	}; //class EntityManager

} // namespace gargantua::ecs
