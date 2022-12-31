/*
gargantua/ecs/entity_manager.ixx

PURPOSE:

CLASSES:

DESCRIPTION:
	
	https://skypjack.github.io/2019-05-06-ecs-baf-part-3/
	

TODO:
	-how to check if i cannot create another entity because 2^16 ids are in use?
*/

export module gargantua.ecs.ecs:entity_manager;

import <cstddef>;
import <set>;
import <vector>;

import :entity;

import gargantua.types;
import gargantua.generator.natural_number_generator;



export namespace gargantua::ecs
{

	class EntityManager
	{
	public:
		EntityManager() : g(0), available(0), next(0) 
		{
			
		}


		/*
		* Creates an entity id and register it to the living entities.
		* Complexity: O(1).
		*/
		[[nodiscard("Entity's id must not be ignored for id leak")]]
		auto CreateEntity() -> entity_t;


		/*
		* Destroys an entity and put its id in a container for reuse.
		* Complexity: O(1).
		*/
		auto DestroyEntity(entity_t e_id) -> void;


		/*
		* Check if an entity is currently used. The check is based on the generation part.
		* The entity must be a valid entity or the result is not valid.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		auto IsAlive(entity_t e) -> bool
		{
			return entities[EntityManipulation::ExtractID(e)] == e;
		}


	private:
		generator::NaturalNumberGenerator<id_t> g;
		std::vector<entity_t> entities;
		natural_t available;

		//contains the entity (that is the index in the entities) that can be recycled.
		entity_t next;
	}; //class EntityManager

} //namespace gargantua::ecs
