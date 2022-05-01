#pragma once
/*
Gargantua/Renderer/RendererComponents.hpp

PURPOSE: Define the components related to rendering.

CLASSES:
	SpriteComponent: keep a texture2d (sprite).
	OrthoCameraComponent: ortho camera component with info about position, rotation and projection.


DESCRIPTION:
	Components are defined to be struct with only data. Constructors are allowed to simplify the initialization of a 
	component. Some of the components have defined the conversion operator to keep the code simple and to avoid 
	repetitions such as sprite1.sprite to access the data (honestly i don't know if it is a good idea to do this).
*/


#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec3d.hpp"
#include "Gargantua/Math/Mat4d.hpp"
#include "Gargantua/Math/Functions.hpp"

#include "Gargantua/Renderer/Texture2d.hpp"

#include <utility>


namespace Gargantua
{
	namespace Renderer
	{
		struct SpriteComponent
		{
			SpriteComponent() = default;

			SpriteComponent(SharedRes<Renderer::Texture2d> sprite_) : sprite(std::move(sprite_))
			{

			}

			operator SharedRes<Renderer::Texture2d>& ()
			{
				return sprite;
			}

			operator const SharedRes<Renderer::Texture2d>& () const
			{
				return sprite;
			}

			Renderer::Texture2d& operator*()
			{
				return *sprite;
			}

			SharedRes<Renderer::Texture2d> sprite;
		};



		struct OrthoCameraComponent
		{
			OrthoCameraComponent() = default;

			OrthoCameraComponent(real_t l, real_t b, real_t r, real_t t, real_t n, real_t f) : position(), rotation(0.0f),
				projection(Math::Projection::Orthographic(l, b, r, t, n, f)),
				view(1.0f), proj_view()
			{
				proj_view = projection * view;
			}


			OrthoCameraComponent(real_t l, real_t b, real_t r, real_t t) : position(), rotation(0.0f),
				projection(Math::Projection::Orthographic(l, b, r, t)),
				view(1.0f), proj_view()
			{
				proj_view = projection * view;
			}


			operator Math::Mat4df& ()
			{
				return proj_view;
			}

			operator const Math::Mat4df& () const
			{
				return proj_view;
			}


			Math::Vec3df position;
			real_t rotation; //rotate around the z axis. counterclock for positive values.

			Math::Mat4df projection;
			Math::Mat4df view;
			Math::Mat4df proj_view; //read from right to left :).
		};
	} //namespace Renderer
} //namespace Gargantua