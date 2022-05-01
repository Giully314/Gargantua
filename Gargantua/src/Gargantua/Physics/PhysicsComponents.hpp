#pragma once
/*
Gargantua/Physics/PhysicsComponents.hpp

PURPOSE: Define components related to physics.

CLASSES:
	TransformComponent: represent an entity in the world with a position, size and orientation.



DESCRIPTION:
	Components are defined to be struct with only data. Constructors are allowed to simplify the initialization of a 
	component. Some of the components have defined the conversion operator to keep the code simple and to avoid 
	repetitions such as sprite1.sprite to access the data (honestly i don't know if it is a good idea to do this).


*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec2d.hpp"

namespace Gargantua
{
	namespace Physics
	{
		struct TransformComponent
		{
			TransformComponent() = default;

			TransformComponent(float x, float y) : position(x, y)
			{

			}

			TransformComponent(Math::Vec2df position_, Math::Vec2df scale_, real_t rotation_) : position(std::move(position_)),
				scale(std::move(scale_)), rotation(rotation_)
			{

			}


			Math::Vec2df position;
			Math::Vec2df scale{ 1.0f, 1.0f };
			real_t rotation = 0.0f; //counterclock for positive values
		};
	} //Physics
} //Gargantua