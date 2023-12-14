/*
* gargantua/game/cell/cell_particle.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
*/

export module gargantua.cell.particle;

import gargantua.math.vector;
import gargantua.ecs.entity;

namespace gargantua::cell
{
	export struct Particle
	{
		constexpr explicit Particle() noexcept = default;

		constexpr explicit Particle(const math::Vec2di& vel) noexcept : velocity(vel)
		{

		}

		constexpr explicit Particle(const ecs::entity_t id, const math::Vec2di& vel) noexcept :
			eid(id), velocity(vel)
		{

		}

		// For the rendering.
		ecs::entity_t eid = ecs::null_entity;

		// velocity in the 2d grid.
		math::Vec2di velocity{};
	};
} // namespace gargantua::cell