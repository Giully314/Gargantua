/*
* gargantua/render/render_components.ixx
* 
* PURPOSE: Render components for ECS.
* 
* CLASSES:
*	TransformComponent: basic info for rendering an entity.
*	TextureComponent: texture for an entity.
*	CameraComponent: info about the camera.
* 
* DESCRIPTION:
*	A set of components used by the render system to work on entities that have them. 
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
*	// now can use the camera
*	
*/

export module gargantua.render.render_components;

import gargantua.types;
import gargantua.render.texture2d;
import gargantua.render.texture_system;
import gargantua.render.camera;
import gargantua.math.math;


export namespace gargantua::render
{
	struct TransformComponent
	{
		TransformComponent() = default;

		TransformComponent(const math::Vec3df& position_, const math::Vec3df& scale_, const f32 rotation_) :
			position(position_), scale(scale_), rotation(rotation_)
		{

		}

		TransformComponent(const math::Vec3df& position_, const math::Vec3df& scale_) :
			TransformComponent(position_, scale_, 0.0f)
		{

		}


		auto Transform() const -> math::Mat4df
		{
			return math::Transform3d::Translate(position) *
				math::Transform3d::RotateZ(rotation) *
				math::Transform3d::Scale(scale);
		}

		math::Vec3df position;
		math::Vec3df scale{1.0f, 1.0f, 1.0f};
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
		CameraComponent()
		{
			camera.Startup();
		}

		/*CameraComponent(CameraComponent&&) noexcept = default;
		CameraComponent& operator=(CameraComponent&&) noexcept = default;*/

		auto GetProjection() const -> const math::Mat4df&
		{
			return camera.GetProjection();
		}

		Camera camera;
	};
} // namespace gargantua::render