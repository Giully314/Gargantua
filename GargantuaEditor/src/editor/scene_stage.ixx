/*
* editor/scene_stage.ixx
*
* PURPOSE: stage for the scene.
*
* CLASSES:
*	SceneStage: stage that handle the execution of the current scene.
*
* DESCRIPTION:
*	The SceneStage is the last stage executed in the pipeline and it basically interacts with 
*	the current scene. Execute and render in the editor app the current scene.
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

		auto Startup() -> void override;

		auto Run(const time::TimeStep& ts) -> void override;

		auto RenderGUI() -> void override;

	private:
		auto HandleWindowResize() -> bool;

	private:
		non_owned_res<scene::SceneContext> context;
	};
} // namespace gargantua::editor
