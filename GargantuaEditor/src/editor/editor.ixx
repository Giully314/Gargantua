/*
* editor/editor.ixx
* 
* 
*/


export module gargantua.editor.editor;

import gargantua;

namespace gargantua::editor
{
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
		render::OrthoCamera camera{ -2.0f, -2.0f, 2.0f, 2.0f };
		scene::SceneContext context;
	};
	
} // namespace gargantua::editor