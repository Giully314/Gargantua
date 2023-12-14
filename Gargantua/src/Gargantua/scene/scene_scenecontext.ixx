/*
* gargantua/scene/scene_scenecontext.ixx
*
* PURPOSE: Provide representation of a game scene.
*
* CLASSES:
*	SceneContext: informations about the current scene.
*
* 
* DESCRIPTION:
*	The SceneContext is used to manage an instance of a scene. A scene is a container used 
*	to represent a section of the game. It's a building block of a game.
*	Every scene has an ECS and informations about width, height, current entitites and cameras. 
*	We can have multiple scenes and switch between each as we want. An example is to have in the 
*	background the setup of a scene for the next level while playing the current scene 
*	(for example the menu scene).
*	
*	A scene manages the physics and rendering systems to be executed in the right order.
* 
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
import <string_view>;
import <vector>;
import <ranges>;


import gargantua.types;
import gargantua.ecs;
import gargantua.time.time_step;
import gargantua.math;
import gargantua.scene.camera_system;

namespace gargantua::scene
{
	export class Entity;

	export enum class SceneMode : u8
	{
		Editor = 0,
		Simulation,
	};

	export class SceneContext
	{
	public:
		explicit SceneContext() : SceneContext(0, 0)
		{

		}

		explicit SceneContext(const u32 width, const u32 height) : viewport_width(width), viewport_height(height), 
			camera_system(&ecs_system), mode(SceneMode::Editor)
		{

		}

		/*
		* Create an empty entity.
		*/
		[[nodiscard]]
		auto CreateEntity() -> Entity;

		/*
		* Create an entity with the tag component attached.
		*/
		[[nodiscard]]
		auto CreateEntity(const std::string_view name) -> Entity;


		/*
		* Get all the active entities in the scene.
		*/
		[[nodiscard]]
		auto GetEntities() const -> const std::vector<ecs::entity_t>&
		{
			return entities;
		}

		/*
		* Destroy the entity.
		*/
		auto DestroyEntity(Entity e) -> void;
		auto DestroyEntity(ecs::entity_t e) -> void;


		/*
		* Get the ECS system used by this scene.
		*/
		[[nodiscard]]
		auto ECS() -> ecs::ECSSystem&
		{
			return ecs_system;
		}


		/*
		* Initialize the scene. 
		*/
		auto Startup() -> void;

		/*
		* Close the scene.
		*/
		auto Shutdown() -> void;

		/*
		* Execute a step of the scene if possible. 
		* This means to execute the physics and rendering system.
		*/
		auto Run(const time::TimeStep& ts) -> void;
		
		/*
		* Run the simulation.
		*/
		auto SimulationMode() -> void
		{
			mode = SceneMode::Simulation;
		}
		
		/*
		* Editor mode.
		*/
		auto EditorMode() -> void
		{
			mode = SceneMode::Editor;
		}


		/*
		* Register an entity to the physics system; basically attaches all the physics 
		* components to the entity.
		*/
		auto RegisterToPhysics(const Entity e, const f32 mass, const math::Vec2df& size) -> void;

		
		/*
		* Register an entity to the rendering system; basically attaches all the render
		* components to the entity.
		*/
		auto RegisterToRenderer(Entity e) -> void;

		/*
		* Create a camera.
		*/
		auto CreateCamera(const std::string& name) -> ecs::entity_t
		{
			auto e = camera_system.Create(name, viewport_width, viewport_height);
			entities.push_back(e);
			return e;
		}

		/*
		* Set the camera to be used for rendering.
		*/
		auto SetActiveCamera(const std::string& name) -> void
		{
			active_camera = camera_system.Get(name);
		}

		/*
		* Get the camera system.
		*/
		auto GetCameraSystem() -> CameraSystem&
		{
			return camera_system;
		}

		/*
		* Get the entity active camera.
		*/
		[[nodiscard]]
		auto GetActiveCamera() -> Entity;


		/*
		* Compute projection* view from the active camera and returns it.
		*/
		[[nodiscard]]
		auto GetActiveCameraMatrix() -> math::Mat4df;

		/*
		* Set the viewport matrix.
		*/
		auto SetViewport(u32 width, u32 height) -> void;
		
		/*
		* Get the viewport dimensions.
		*/
		auto GetViewport() const noexcept -> math::Vec2d<u32>
		{
			return math::Vec2d<u32>{viewport_width, viewport_height};
		}

		
		/*
		* Return a view of all the entities that are alive.
		*/
		auto GetEntities()
		{
			return std::views::all(entities);
		}


	private:
		ecs::ECSSystem ecs_system; // must be created before camera system.
		CameraSystem camera_system;
		ecs::entity_t active_camera = ecs::null_entity;

		// THis is temporary. The future code will be a map from unique engine id to entitites.
		std::vector<ecs::entity_t> entities;
		
		u32 viewport_width;
		u32 viewport_height;
		SceneMode mode = SceneMode::Editor;
	};
} // namespace gargantua::scene
