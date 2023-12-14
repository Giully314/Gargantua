/*
* gargantua/ecs/ecs_entity.ixx
* 
* PURPOSE: Provide a definition of entity.
* 
* CLASSES:
*	EntityManipulation: Contains a set of functions for id manipulation.
* 
* DESCRIPTION:
*	An entity is a 32 bit id composed of 2 parts: a generation part of 6 bits (most significant)
*	and an entity part of 26 bits (least significant).
*	The generation part is used for recyling purpose; the entity part is used to access components and other 
*	functionalities inside the ecs.
*	
*	The EntityManipulation struct is primarily used inside the ecs module to extract the generation and entity from an id.
*	It can be used by the user too for additional checks.
* 
* 
* USAGE:
*	entity_t e = create_entity();
*	...
*	auto generation = EntityManipulation::Generation(e);
*	auto entity = EntityManipulation::Entity(e);
*	
*	++generation;
*	auto new_id = EntityManipulation::MakeID(generation, entity);
*/

export module gargantua.ecs.entity;

import <limits>;

import gargantua.types;

namespace gargantua::ecs
{
	export using id_t = u32;
	export using entity_t = u32;

	inline constexpr u32 bits_for_entity = 26;
	inline constexpr u32 bits_for_generation = (sizeof(id_t) * 8) - bits_for_entity;
	inline constexpr id_t entity_mask = ~id_t{ 0 } >> bits_for_generation;
	inline constexpr id_t generation_mask = ~id_t{ 0 } << bits_for_entity;


	// 0xffff_ffff
	inline constexpr id_t null_id = std::numeric_limits<id_t>::max();
	export inline constexpr entity_t null_entity = null_id;
	
	export struct EntityManipulation
	{
		// Return an id_t with the generation part and the entity part set to 0.
		[[nodiscard]]
		static constexpr auto RawGeneration(const entity_t id) -> id_t
		{
			return (id & generation_mask);
		}

		// Return the generation part.
		[[nodiscard]]
		static constexpr auto Generation(const entity_t id) -> id_t
		{
			return id >> bits_for_entity;
		}

		// Return the entity part.
		[[nodiscard]]
		static constexpr auto Entity(const entity_t id) -> id_t
		{
			return id & entity_mask;
		}

		// Return a new id with the generation and entity passed.
		[[nodiscard]]
		static constexpr auto MakeID(const id_t generation, const id_t entity) -> entity_t
		{
			//TODO: assert to check id and gen are in the correct range.
			entity_t id = (generation << bits_for_entity) | entity;
			return id;
		}

		// Return an id with the entity part updated.
		[[nodiscard]]
		static constexpr auto InsertEntityInID(entity_t id, const id_t entity) -> entity_t
		{
			id &= ~entity_mask;
			id |= entity;
			return id;
		}

		// Return an id with the generation part updated.
		[[nodiscard]]
		static constexpr auto InsertGenerationInID(entity_t id, const id_t gen) -> entity_t
		{
			id &= ~generation_mask;
			id |= (gen << bits_for_entity);
			return id;
		}
	};
} // namespace gargantua::ecs


