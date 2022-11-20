/*
gargantua/ecs/ecs_types.ixx

PURPOSE:

CLASSES:

DESCRIPTION:


*/

export module gargantua.ecs.ecs_types;

import <cstdint>;


export namespace gargantua::ecs
{
	using id_t = std::uint32_t;
	using half_id_t = std::uint16_t;

	using entity_t = id_t;
	inline constexpr entity_t null_entity = 0;
} //namespace gargantua::ecs