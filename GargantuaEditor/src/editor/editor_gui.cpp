/*
* 
*/

module;

#include <imgui.h>

module gargantua.editor.editor_gui;


namespace gargantua::editor
{
    auto EditorGUI::Startup() -> void
    {
        entities.push_back(context->CreateEntity());
    /*    entities.push_back(context->CreateEntity());
        entities.push_back(context->CreateEntity());
        entities.push_back(context->CreateEntity());*/

        for (auto& entity : entities)
        {
            context->RegisterToPhysics(entity, 1.0f);
            context->RegisterToRenderer(entity);
        }


    }

	auto EditorGUI::RenderGUI() -> void 
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        ImGuiIO& io = ImGui::GetIO();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Scene manager");
            


        ImGui::End();
        ImGui::PopStyleVar();
	}

} // namespace gargantua::editor