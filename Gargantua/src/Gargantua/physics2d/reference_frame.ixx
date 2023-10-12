/*
* gargantua/physics/reference_frame.ixx
* 
* PURPOSE: define the reference frame and coordinates used in the game engine.
* 
* DESCRIPTION:
*	The main reference frame is the center of the screen at the start with 
*	positive y going up, and positive x going right.
* 
* TODO: 
*	Add more info about the transformations and reference frames used in the physics world.
*/

export module gargantua.physics2d.reference_frame;

import gargantua.math.vec2d;

namespace gargantua::physics2d
{
	struct ReferenceFrame
	{
		inline static math::Vec2df origin{0.0f, 0.0f};
		inline static math::Vec2df i_dir{1.0f, 0.0f};
		inline static math::Vec2df j_dir{0.0f, 1.0f};
	};
} // namespace gargantua::physics