/*
* gargantua/render/render_components.ixx
* 
* PURPOSE: Render components for ECS.
* 
* CLASSES:
*	TransformComponent:
*	TextureComponent:
*	CameraComponent:
* 
* DESCRIPTION:
* 
* USAGE:
*	
*/

export module gargantua.render.render_components;

import gargantua.types;
import gargantua.render.texture2d;
import gargantua.render.texture_system;
import gargantua.math.math;


export namespace gargantua::render
{
	struct TransformComponent
	{
		TransformComponent() = default;

		TransformComponent(const math::Vec2df& position_, const math::Vec2df& scale_, const f32 rotation_) :
			position(position_), scale(scale_), rotation(rotation_)
		{

		}

		TransformComponent(const math::Vec2df& position_, const math::Vec2df& scale_) :
			TransformComponent(position_, scale_, 0.0f)
		{

		}


		math::Vec2df position;
		math::Vec2df scale{1.0f, 1.0f};
		f32 rotation = 0.0f;
	};


	struct TextureComponent
	{
		TextureComponent() : texture(TextureSystem::Instance().Get("WhiteTexture"))
		{

		}

		TextureComponent(const shared_res<Texture2d>& texture_) : texture(texture_)
		{

		}

		shared_res<Texture2d> texture;
	};


	struct CameraComponent
	{
		math::Mat4df view_projection;
	};
} // namespace gargantua::render