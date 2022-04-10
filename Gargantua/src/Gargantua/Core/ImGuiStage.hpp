#pragma once
/*
PURPOSE: Stage setup for imgui.

CLASSES:
	ImGuiStage: Stage for ImGui operations.

DESCRIPTION:
	Stage for preparation of the imgui context at every application update.

USAGE:


*/

#include "Gargantua/Core/Stage.hpp"
#include "Gargantua/Time/TimeStep.hpp"
#include "Gargantua/Core/Window.hpp"


namespace Gargantua
{
	namespace Core
	{
		class ImGuiStage : public Stage
		{
		public:
			ImGuiStage(SharedRes<Window> window_);

			~ImGuiStage();


			void Start() override;

			void Execute(const Time::TimeStep&) override;

			void RenderGUI() override;

			void End() override;

		private:
			SharedRes<Window> window;
		};
	} //namespace Core 
} //namespace Gargantua

