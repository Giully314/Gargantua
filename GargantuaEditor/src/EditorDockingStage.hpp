#pragma once
/*
EditorDockingStage.hpp

PURPOSE: Docking with Dead ImGui.

CLASSES:
	EditorDockingStage: Stage for first setup imgui and docking.

DESCRIPTION:
	Simple stage for setup imgui and docking for now.
*/

#include <Gargantua/Types.hpp>

#include <Gargantua/Core/Stage.hpp>

#include <Gargantua/Time/TimeStep.hpp>



namespace Gargantua
{
	namespace Editor
	{
		class EditorDockingStage : public Core::Stage
		{
		public:
			EditorDockingStage() : Stage("EditorDockingStage")
			{

			}

			// Inherited via Stage
			virtual void Start() override;
			virtual void End() override;
			virtual void Execute(const Time::TimeStep& ts) override;
			virtual void RenderGUI() override;
		};

	} //namespace Editor
} //namespace Gargantua

