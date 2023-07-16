/*
* gargantua/scene/editor_system.ixx
* 
* 
* PURPOSE:
*/


export module gargantua.scene.editor_system;

import gargantua.types;
import gargantua.ecs.ecs;

namespace gargantua::scene
{
	export
	class EditorSystem : public Singleton<EditorSystem>
	{
	public:

		auto Run(ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance()) -> void;

	};
} // namespace gargantua::scene