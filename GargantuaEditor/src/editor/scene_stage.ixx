/*
* editor/scene_stage.ixx
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

export module gargantua.editor.scene_stage;


import gargantua;

namespace gargantua::editor
{
	export
	class SceneStage : public app::Stage
	{
	public:
		SceneStage(non_owned_res<scene::SceneContext> context_) : app::Stage("SceneStage"),
			context(context_)
		{

		}

		auto Run(const time::TimeStep& ts) -> void override;

		auto RenderGUI() -> void override;

	private:
		non_owned_res<scene::SceneContext> context;
	};
} // namespace gargantua::editor
