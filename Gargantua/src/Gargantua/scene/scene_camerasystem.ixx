/*
* gargantua/scene/scene_camerasystem.ixx
*
* PURPOSE: Manage cameras in a scene.
*
* CLASSES:
*	CameraSystem: Singleton for managing cameras in a scene.
* 
* DESCRIPTION:
*	The camera system is used in all Scene objects to easily manages all the cameras.
*
* 
* USAGE:
*	CameraSystem cam_sys{ecs_sys};
*	
*
*	entity_t camera_entity cam_sys.Create(camera_name, width, height);
* 
*	...
* 
*	cam_sys.Destroy(camera_name);
*
*/


export module gargantua.scene.camera_system;

import <vector>;
import <functional>;
import <string>;
import <string_view>;
import <ranges>;

import gargantua.types;
import gargantua.ecs;
import gargantua.scene.ecs_components;

namespace gargantua::scene
{
	export class CameraSystem
	{
	public:
		explicit CameraSystem(non_owned_res<ecs::ECSSystem> ecs_system_) : ecs_system(ecs_system_)
		{

		}

		//auto Destroy(ecs::entity_t id) -> void;
		
		/*
		* Destroy a camera.
		*/
		auto Destroy(const std::string_view name) -> void;

		/*
		* Get the number of cameras.
		*/
		[[nodiscard]]
		auto Size() const noexcept -> u32
		{
			return static_cast<u32>(cameras.size());
		}


		/*
		* Get the entity camera with the name passed.
		*/
		[[nodiscard]]
		auto Get(const std::string_view name) -> ecs::entity_t;

		/*
		* Create a camera.
		*/
		auto Create(const std::string_view name, u32 viewport_width, u32 viewport_height) -> ecs::entity_t;
	
	private:
		non_owned_res<ecs::ECSSystem> ecs_system;

		// TODO: use transparent comparator? 
		//std::unordered_map<std::string, ecs::entity_t> cameras;
		std::vector<ecs::entity_t> cameras;
	};
} // namespace gargantua::scene
