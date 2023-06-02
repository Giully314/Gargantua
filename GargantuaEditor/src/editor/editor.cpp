/*
* 
*/

module gargantua.editor.editor;

import gargantua.editor.editor_gui;
import gargantua.editor.scene_stage;

namespace gargantua::editor
{
	auto Editor::Startup() -> void 
	{
		context.Startup();
		pipeline.AddStage<EditorGUI>(&context);
		pipeline.AddStage<SceneStage>(&context);
		pipeline.Startup();
	}

	auto Editor::Shutdown() -> void 
	{
		pipeline.Shutdown();
	}
	
	auto Editor::Begin() -> void 
	{
		// Begin renderer
		render::Renderer2dSystem::Instance().BeginScene(camera.GetViewProjection());
	}
	
	auto Editor::End() -> void 
	{
		// End renderer
		render::Renderer2dSystem::Instance().EndScene();
	}
	
	auto Editor::Run(const time::TimeStep& ts) -> app::ApplicationState 
	{
		pipeline.Run(ts);
		return app::ApplicationState::Running;
	}
	
	auto Editor::RenderGUI() -> void 
	{
		pipeline.RenderGUI();
	}

} // namespace gargantua