/*
* gargantua/cell/cell_particles.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
*/

export module gargantua.cell.particles;

import gargantua.cell.particle;
import gargantua.ecs.entity;
import gargantua.math.vector;


export namespace gargantua::cell
{
	struct EmptyParticle : Particle
	{

	};


	struct SandParticle : Particle
	{
		constexpr explicit SandParticle() noexcept : Particle{ math::Vec2di{1, 1} }
		{

		}	

		constexpr explicit SandParticle(const ecs::entity_t id) noexcept : Particle{ id, math::Vec2di{1, 1} }
		{

		}
	};
} // namespace gargantua::cell

