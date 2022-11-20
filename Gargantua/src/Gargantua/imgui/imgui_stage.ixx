/*
gargantua/imgui/imgui_stage.ixx


PURPOSE: Stage setup for imgui.

CLASSES:
	ImGuiStage: Stage for ImGui operations.

DESCRIPTION:
	Stage for preparation of the imgui context at every application update.

USAGE:


*/


export module gargantua.imgui.imgui_stage;

import gargantua.types;

import gargantua.core.window;
import gargantua.core.stage;

import gargantua.time.time_step;

namespace gargantua::imgui
{

	export class ImGuiStage : public core::Stage
	{
	public:
		ImGuiStage(const SharedRes<core::Window>& window_);

		~ImGuiStage();


		void Start() override;

		void Execute(const time::TimeStep&) override;

		void RenderGUI() override;

		void End() override;

	private:
		SharedRes<core::Window> window;
	}; //class ImGuiStage

} //namespace gargantua::imgui

