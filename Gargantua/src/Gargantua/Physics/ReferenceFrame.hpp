#pragma once
/*
Gargantua/Physics/ReferenceFrame.hpp

PURPOSE: Define a reference frame of the world.

CLASSES:
	ReferenceFrame: defines vector that describe the reference frame of the physics world.

DESCRIPTION:
	The reference frame is defined with i_dir being the x direction pointing to the right for positive values;
	j_dir being the y direction pointing above for positive values.
	o is the origin.
	i_dir and j_dir are unit vectors.

	y ^
	  |
	  |
	  |
	  o------> x


	Usually there are 2 reference frames used: the first is the world reference frame(WRF) and second is the body 
	reference frame(BRF). Scale and rotation are done in the BRF while the translation is done with respect to WRF.

	Rotation are counterclockwise for positive angles.
*/


#include "Gargantua/Math/Vec2d.hpp"


namespace Gargantua
{
	namespace Physics
	{
		struct ReferenceFrame
		{
			static Math::Vec2df origin;
			static Math::Vec2df i_dir;
			static Math::Vec2df j_dir;
		};
	} //namespace Physics
} //namespace Gargantua