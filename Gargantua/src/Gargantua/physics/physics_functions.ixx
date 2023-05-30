/*
* gargantua/physics/physics_systems.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* TODO:
* 
* USAGE:
*/

export module gargantua.physics.physics_functions;


import gargantua.types;
import gargantua.physics.physics_components;

export namespace gargantua::physics
{
	struct UpdateVelocity
	{
		UpdateVelocity(const f32 dt_) : dt(dt_)
		{

		}

		auto operator()(Force& f, Mass& m, Velocity& v) -> void
		{
			v.v += f.f * m.inv_m * dt;
		}

		const f32 dt;
	};

	struct UpdatePosition
	{
		UpdatePosition(const f32 dt_) : dt(dt_)
		{

		}


		auto operator()(Position& p, Velocity& v) -> void
		{
			p.p += v.v * dt;
		}

		const f32 dt;
	};

} // namespace gargantua::physics