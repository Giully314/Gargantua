/*
* gargantua/scene/editor_system.ixx
* 
* PURPOSE: Run the scene in editor mode.
*/


export module gargantua.scene.editor_system;

import gargantua.types;
import gargantua.ecs;

namespace gargantua::scene
{
	export
	class EditorSystem : NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static
		auto Instance() -> EditorSystem&
		{
			static EditorSystem sys;
			return sys;
		}

		auto Run(ecs::ECSSystem& ecs_s) -> void;

	private:
		EditorSystem() = default;
	};
} // namespace gargantua::scene