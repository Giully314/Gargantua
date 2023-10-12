/*
* editor/editor.cpp
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.editor.editor;

import gargantua.editor.editor_gui;
import gargantua.editor.scene_stage;

namespace gargantua::editor
{
	auto Editor::Startup() -> void 
	{
		GRG_CORE_LOGGER_FILTER(log::Level::debug);
		context.Startup();

		// Demo stage is used to explore the imgui library and add functionalities on the go.
		// pipeline.AddStage<DemoStage>();
		
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
		auto proj_view = context.GetActiveCameraMatrix();
		//GRG_CORE_DEBUG("Editor\n{}\n", proj_view.ToString());
		render::Renderer2dSystem::Instance().BeginScene(proj_view);
	}
	
	auto Editor::End() -> void 
	{
		// End renderer
		render::Renderer2dSystem::Instance().EndScene();
	}
	
	auto Editor::Run(const time::TimeStep& ts) -> app::ApplicationState 
	{
		camera.camera = context.GetActiveCamera();
		camera.Run(ts);
		pipeline.Run(ts);
		return app::ApplicationState::Running;
	}
	
	auto Editor::RenderGUI() -> void 
	{
		pipeline.RenderGUI();
	}

} // namespace gargantua