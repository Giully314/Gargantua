/*
PURPOSE:

DESCRIPTION:
	An entity is formed by a 32bits number composed of the first 16 bits that represent 


*/

export module gargantua.ecs.ecs:entity;

import <cstdint>;
import <limits>;

import gargantua.types;


namespace gargantua::ecs
{
	export using id_t = std::uint32_t;
	export using entity_t = id_t;

	inline constexpr natural_t bits_for_id = 16;
	inline constexpr natural_t bits_for_gen = (sizeof(entity_t) * 8) - bits_for_id;
	inline constexpr entity_t id_mask = ~entity_t{ 0 } << bits_for_id;
	inline constexpr entity_t gen_mask = ~entity_t{ 0 } >> bits_for_gen;
	//inline constexpr entity_t gen_mask = ~entity_t{ 0 } << bits_for_gen;

	//0xffff_ffff
	export inline constexpr entity_t NullEntity = std::numeric_limits<entity_t>::max();


	struct EntityManipulation
	{
		[[nodiscard]]
		static constexpr auto ExtractGeneration(const entity_t e) -> id_t
		{
			return e & gen_mask;
		}
		

		[[nodiscard]]
		static constexpr auto ExtractID(const entity_t e) -> id_t
		{
			return (e & id_mask) >> bits_for_id;
		}


		[[nodiscard]]
		static constexpr auto MakeEntity(const id_t id, const id_t gen) -> entity_t
		{
			//TODO: assert to check id and gen are in the correct range.
			entity_t e = id;
			e = e << bits_for_id;
			e |= gen;
			return e;
		}


		static constexpr auto InsertIdInEntity(entity_t e, const id_t id) -> entity_t
		{
			e &= ~id_mask;
			e |= (id << bits_for_id);
			return e;
		}

		static constexpr auto InsertGenInEntity(entity_t e, const id_t gen) -> entity_t
		{
			e &= ~gen_mask;
			e |= gen;
			return e;
		}
	};
} //namespace gargantua::ecs