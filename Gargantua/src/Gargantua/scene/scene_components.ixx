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


export namespace gargantua::scene
{
	struct TagComponent
	{
		TagComponent() = default;

		TagComponent(const std::string& name_) : name(name_)
		{

		}

		std::string name{"Unknown"};
	};
} // namespace gargantua::scene