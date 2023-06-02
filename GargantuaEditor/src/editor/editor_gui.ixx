/*
* editor/editor_gui.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* USAGE:
* 
*/

export module gargantua.editor.editor_gui;

import <vector>;
import gargantua;

namespace gargantua::editor
{
	export 
	class EditorGUI : public app::Stage
	{
	public:
		EditorGUI(non_owned_res<scene::SceneContext> context_) : app::Stage("EditorGUI"),
			context(context_)
		{

		}

		auto Startup() -> void override;

		auto RenderGUI() -> void override;
	private:
		non_owned_res<scene::SceneContext> context;
		std::vector<scene::Entity> entities;
	};
} // namespace gargantua




