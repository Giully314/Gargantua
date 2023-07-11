/*
* gargantua/physics/reference_frame.ixx
* 
* PURPOSE: define the reference frame used in the game engine.
* 
* 
*/

export module gargantua.physics.reference_frame;

import gargantua.math.vec2d;

namespace gargantua::physics
{
	struct ReferenceFrame
	{
		inline static math::Vec2df origin{0.0f, 0.0f};
		inline static math::Vec2df i_dir{1.0f, 0.0f};
		inline static math::Vec2df j_dir{0.0f, 1.0f};
	};
} // namespace gargantua::physics