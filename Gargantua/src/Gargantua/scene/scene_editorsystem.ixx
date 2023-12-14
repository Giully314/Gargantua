/*
* gargantua/scene/scene_editorsystem.ixx
* 
* PURPOSE: Run the scene in editor mode.
* 
* CLASSES:
*	EditorSystem: singleton for managing the editor scene.
* 
* DESCRIPTION:
*/


export module gargantua.scene.editor_system;

import gargantua.types;
import gargantua.ecs;

namespace gargantua::scene
{
	export class EditorSystem : NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static auto Instance() -> EditorSystem&
		{
			static EditorSystem sys;
			return sys;
		}

		auto Run(ecs::ECSSystem& ecs_s) -> void;

	private:
		explicit EditorSystem() = default;
	};
} // namespace gargantua::scene