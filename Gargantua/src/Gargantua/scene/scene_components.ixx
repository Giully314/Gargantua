/*
* gargantua/scene/scene_components.ixx
* 
* PURPOSE: define scene ecs components.
* 
* CLASSES:
*	TagComponent: name tag attached to an entity.
* 
*/

export module gargantua.scene.scene_components;

import <string>;
import <string_view>;

export namespace gargantua::scene
{
	struct TagComponent
	{
		TagComponent() = default;

		explicit TagComponent(std::string_view name_) : name(name_)
		{

		}

		std::string name{"Unknown"};
	};
} // namespace gargantua::scene