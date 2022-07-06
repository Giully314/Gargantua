/*
EditorDockingStage.cpp
*/

#include "EditorDockingStage.hpp"

#include <imgui.h>


namespace Gargantua
{
	namespace Editor
	{
		void EditorDockingStage::Start()
		{

        }


		void EditorDockingStage::End()
		{

		}


		void EditorDockingStage::Execute(const Time::TimeStep& ts)
		{

		}   

		void EditorDockingStage::RenderGUI()
		{
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());   
		}

	} //namespace Editor
} //namespace Gargantua
