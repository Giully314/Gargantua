/*
* editor/editor.ixx
* 
* PURPOSE: define the editor application.
* 
* CLASSES:
*	DemoStage: stage used only for test purpose with imgui.
*	Editor: application executed by the engine.
* 
* DESCRIPTION:
*	The Editor is the application executed by the engine. The main goal is to register the stages
*	in the pipeline and to provide the basic implementations of the Application base class.
* 
*/

module;

#include <imgui.h>

export module gargantua.editor.editor;

import gargantua;

import gargantua.editor.editor_camera;

namespace gargantua::editor
{
	export
	struct DemoStage : public app::Stage
	{
		auto RenderGUI() -> void override
		{
			bool open = true;
			ImGui::ShowDemoWindow(&open);
		}
	};

	export 
	class Editor : public app::Application
	{
	public:
		auto Startup() -> void override;
		auto Shutdown() -> void override;
		auto Begin() -> void override;
		auto End() -> void override;
		auto Run(const time::TimeStep& ts) -> app::ApplicationState override;
		auto RenderGUI() -> void override;

	private:
		//render::OrthoCamera camera{ -1.0f, -1.0f, 1.0f, 1.0f };
		//render::OrthoCamera camera{ -1.0f, -1.0f, 1.0f, 1.0f };
		//EditorCamera camera;
		scene::SceneContext context;
		EditorCamera camera;
	};
	
} // namespace gargantua::editor