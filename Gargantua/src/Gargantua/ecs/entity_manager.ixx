/*
gargantua/ecs/entity_manager.ixx

PURPOSE:

CLASSES:

DESCRIPTION:
	https://skypjack.github.io/2019-05-06-ecs-baf-part-3/
	

*/

export module gargantua.ecs.entity_manager;

import <cstddef>;
import <set>;
import <vector>;

import gargantua.types;

import gargantua.ecs.ecs_types;

import gargantua.generator.natural_number_generator;



export namespace gargantua::ecs
{

	class EntityManager
	{
	public:
		EntityManager() : g(0), available(0), next(0), num_of_bits_for_entity(16), generation_mask(0xffff),
			entity_mask(0xffff0000)
		{
			//Initiliaze the vector with the null entity with id 0.
			entities.push_back(g.Get());
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
		* Complexity: O(1).
		*/
		[[nodiscard]]
		auto IsAlive(entity_t e) -> bool
		{
			return ExtractGeneration(entities[ExtractEntity(e)]) == ExtractGeneration(e);
		}


	private:
		generator::NaturalNumberGenerator<half_id_t> g;
		std::vector<entity_t> entities;
		natural_t available;

		//contains the entity (that is the index in the entities) that can be recycled.
		entity_t next;

		const natural_t num_of_bits_for_entity;
		const entity_t generation_mask;
		const entity_t entity_mask;

	private:
		[[nodiscard]]
		auto ExtractEntity(entity_t e) -> entity_t
		{
			return e >> num_of_bits_for_entity;
		}
		
		/*
		* Insert the entity into the first 16 bit of id.
		* The entity is just a number represented in the least 16 bits.
		*/
		[[nodiscard]]
		auto InsertEntity(id_t entity, id_t id) -> entity_t
		{
			//clear the entity part
			id &= generation_mask;
			return (entity << num_of_bits_for_entity) | id;
		}


		[[nodiscard]]
		auto ExtractGeneration(entity_t e) -> entity_t
		{
			return e & generation_mask;
		}


		[[nodiscard]]
		auto CreateEntityID() -> entity_t
		{
			id_t id = g.Get();
			return id << num_of_bits_for_entity;
		}
	}; //class EntityManager

} //namespace gargantua::ecs
