/*
* gargantua/scene/scene_context.ixx
*
* PURPOSE: Represent a scene.
*
* CLASSES:
*	SceneContext: informations and API about the current scene.
*
* DESCRIPTION:
*	The SceneContext is used to manage an instance of a scene. 
* 
* USAGE:
*	SceneContext context(width, height);
*	
*	Entity e1 = context.CreateEntity();
*	
*	// Register the entity to physics and render.
*	context.RegisterToPhysics(e1);
*	context.RegisterToRender(e1);
*	
*	// Create a camera;
*	context.CreateCamera(camera_name);
*	context.SetActiveCamera(camera_name);
*	
*	// Execute all ecs systems
*	context.Run(time_step);
*	
*	context.Destroy(e1);
*	
*/

export module gargantua.scene.scene_context;

import <string>;
import <vector>;

import gargantua.types;
import gargantua.ecs.ecs;
import gargantua.time.time_step;
import gargantua.math.math;
import gargantua.scene.camera_system;

namespace gargantua::scene
{
	export
	class Entity;

	export
	class SceneContext
	{
	public:
		SceneContext() : SceneContext(0, 0)
		{

		}

		SceneContext(u32 width, u32 height) : viewport_width(width), viewport_height(height), 
			camera_system(&ecs_system)
		{

		}

		[[nodiscard]]
		auto CreateEntity() -> Entity;

		[[nodiscard]]
		auto CreateEntityFromID(const ecs::entity_t e) -> Entity;

		[[nodiscard]]
		auto GetEntities() const -> const std::vector<ecs::entity_t>&
		{
			return entities;
		}

		auto DeleteEntity(Entity e) -> void;
		auto DeleteEntity(ecs::entity_t e) -> void;


		[[nodiscard]]
		auto ECS() -> ecs::ECSSystem&
		{
			return ecs_system;
		}


		auto Startup() -> void;
		auto Shutdown() -> void;

		auto Run(const time::TimeStep& ts) -> void;
		
		auto Play() -> void
		{
			is_running = true;
		}
		
		auto Stop() -> void
		{
			is_running = false;
		}


		auto RegisterToPhysics(Entity e, f32 mass) -> void;
		auto RegisterToRenderer(Entity e) -> void;


		auto CreateCamera(const std::string& name) -> ecs::entity_t
		{
			return camera_system.Create(name, viewport_width, viewport_height);
		}

		// From 0 to num_of_cameras
		auto SetActiveCamera(const std::string& name) -> void
		{
			active_camera = camera_system.Get(name);
		}


		auto GetCameraSystem() -> CameraSystem&
		{
			return camera_system;
		}


		[[nodiscard]]
		auto GetActiveCamera() -> Entity;


		// Compute projection * view.
		[[nodiscard]]
		auto GetActiveCameraMatrix() -> math::Mat4df;


		auto SetViewport(u32 width, u32 height) -> void;
		
		auto GetViewport() const noexcept -> math::Vec2d<u32>
		{
			return math::Vec2d<u32>{viewport_width, viewport_height};
		}


	private:
		ecs::ECSSystem ecs_system; // must be created before camera system.
		CameraSystem camera_system;
		ecs::entity_t active_camera = ecs::null_entity;

		// THis is temporary. The future code will be a map from unique engine id to entitites.
		std::vector<ecs::entity_t> entities;
		
		u32 viewport_width;
		u32 viewport_height;
		bool is_running = true;
	};
} // namespace gargantua::scene
