#pragma once

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
			ImGuiStage(NonOwnedRes<Window> window_);

			~ImGuiStage();


			void Start() override;

			void Execute(const Time::TimeStep&) override;

			void RenderGUI() override;

			void End() override;

		private:
			NonOwnedRes<Window> window;
		};
	} //namespace Core 
} //namespace Gargantua

