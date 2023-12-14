/*
* gargantua/scene/scene_ecscomponents.ixx
* 
* PURPOSE: define scene ecs components.
* 
* CLASSES:
*	TagComponent: name tag attached to an entity.
* 
*/

export module gargantua.scene.ecs_components;

import <string>;
import <string_view>;

export namespace gargantua::scene
{
	struct TagComponent
	{
		constexpr explicit TagComponent() = default;

		constexpr explicit TagComponent(std::string_view name_) : name(name_)
		{

		}

		std::string name{"Unknown"};
	};
} // namespace gargantua::scene