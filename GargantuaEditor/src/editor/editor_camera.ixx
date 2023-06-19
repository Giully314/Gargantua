/*
* editor/editor_camera.ixx
* 
* PURPOSE: Manage editor camera.
* 
*/

export module gargantua.editor.editor_camera;


import gargantua;

namespace gargantua::editor
{
	export 
	class EditorCamera
	{
	public:
		auto Run(const time::TimeStep& ts) -> void;
		f32 velocity = 1.0f;

		scene::Entity camera;
	};
} // namespace gargantua::editor