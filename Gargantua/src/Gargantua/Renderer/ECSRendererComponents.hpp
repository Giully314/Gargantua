#pragma once
/*
Gargantua/Renderer/ECSRendererComponents.hpp

PURPOSE:

CLASSES:
	TransformComponent: informations about the position, orientation and scaling of the shape.
	ColorComponent: color of the entity.
	OrthoCameraComponent: informations about the camera.

DESCRIPTION:
	These components describe an entity in the "renderer" world.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec2d.hpp"
#include "Gargantua/Math/Vec4d.hpp"
#include "Gargantua/Math/Mat4d.hpp"



namespace Gargantua
{
	namespace Renderer
	{
		struct TransformComponent
		{
			Math::Vec2df position;
			Math::Vec2df scale{1, 1};
			real_t rotation = 0.0f;
		};

		
		struct ColorComponent
		{
			Math::Vec4df color{ 1.0f, 1.0f, 0.0f, 1.0f };
		};


		struct OrthoCameraComponent
		{
			real_t zoom_level = 5.0f;
			real_t aspect_ratio = 16.0f / 10.0f;
			Math::Mat4df projection;
			Math::Mat4df projection_view; //read from right to left
		};
	} //namespace Renderer
} //namespace Gargantua


