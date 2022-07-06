#pragma once
/*
Gargantua/Input/ECSInputComponents.hpp

PURPOSE: Input components for ecs.

CLASSES:
	MoveActionComponent: map the input to movement.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec2d.hpp"

#include <utility>


namespace Gargantua
{
	namespace Input
	{
		struct MoveActionComponent
		{
			std::pair<key_t, Math::Vec2df> up;
			std::pair<key_t, Math::Vec2df> down;
			std::pair<key_t, Math::Vec2df> right;
			std::pair<key_t, Math::Vec2df> left;

			Math::Vec2df net;
		};
	} //namespace Input
} //namespace Gargantua