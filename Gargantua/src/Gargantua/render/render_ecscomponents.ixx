/*
* gargantua/render/render_ecscomponents.ixx
*
* PURPOSE: Provide render components for ECS.
*
* CLASSES:
*	TransformComponent: info for rendering an entity.
*	TextureComponent: texture for an entity.
*	CameraComponent: info about the camera.
*
* DESCRIPTION:
*	A set of components used by the 2d render system to work on entities that have them.
*	The Transform and Texture components are necessary to every entity in the game that must
*	be displayed in the screen.
*	The CameraComponent contains all the information about the camera. This method allow to attach
*	a camera to the player entity and have the camera looked.
*
* USAGE:
*
*	// Create an entity camera
*	ecs.Emplace<TransformComponent>(camera);
*	ecs.Emplace<CameraComponent>(camera);
*
*/

export module gargantua.render.ecs_components;

import gargantua.types;
import gargantua.math;
import gargantua.render.camera;
import gargantua.render.texture;
import gargantua.render.texture_system;


export namespace gargantua::render
{
	struct TransformComponent
	{
		constexpr explicit TransformComponent() = default;

		constexpr explicit TransformComponent(const math::Vec3df& position_, const math::Vec3df& scale_, const f32 rotation_) 
			: position(position_), scale(scale_), rotation(rotation_)
		{

		}

		constexpr explicit TransformComponent(const math::Vec3df& position_, const math::Vec3df& scale_) :
			TransformComponent(position_, scale_, 0.0f)
		{

		}


		constexpr auto Transform() const noexcept -> math::Mat4df
		{
			return math::Transform3d::Translate(position) *
				math::Transform3d::RotateZ(rotation) *
				math::Transform3d::Scale(scale);
		}

		math::Vec3df position;
		math::Vec3df scale{ 1.0f, 1.0f, 1.0f };
		f32 rotation = 0.0f;
	};


	struct TextureComponent
	{
		explicit TextureComponent() = default;

		explicit TextureComponent(const shared_res<Texture>& texture_,
			const math::Vec4df& color_, const f32 tiling_factor_) 
			: texture(texture_), color(color_), tiling_factor(tiling_factor_)
		{

		}

		explicit TextureComponent(const shared_res<Texture>& texture_) : texture(texture_)
		{

		}

		shared_res<Texture> texture;
		math::Vec4df color{ 1.0f, 1.0f, 1.0f, 1.0f };
		f32 tiling_factor = 1.0f;
	};



	struct CameraComponent
	{
		explicit CameraComponent()
		{
			camera.Startup();
		}

		/*CameraComponent(CameraComponent&&) noexcept = default;
		CameraComponent& operator=(CameraComponent&&) noexcept = default;*/

		constexpr auto Projection() const noexcept -> const math::Mat4df&
		{
			return camera.Projection();
		}

		render::Camera camera;
	};
} // namespace gargantua::render