/*
* editor/editor_gui.cpp
*/

module;

#include <imgui.h>
//#include <misc/cpp/imgui_stdlib.h>

module gargantua.editor.editor_gui;

#define MAX_TEXT_LEN 64


namespace gargantua::editor
{
    // *********************************************** UTILITY FUNCTIONS IMGUI DRAW ******************************
    
    static auto DrawFloat(std::string_view name, f32& f) -> void
    {
        ImGui::DragFloat(name.data(), &f, 0.01f, -3.0f, 3.0f);
    }
    
    static auto DrawVec3d(std::string_view name, math::Vec3df& v) -> void
    {
        ImGui::DragFloat3(name.data(), &v.x, 0.01f, -3.0f, 3.0f);
    }

    static auto DrawText(std::string_view name, std::string& s) -> void
    {
        char text[MAX_TEXT_LEN] = {};
        s.copy(text, MAX_TEXT_LEN);
        if (ImGui::InputText(name.data(), text, MAX_TEXT_LEN))
        {
            s = text;
        }

        // Impossible to use with misc/..., error in building for conflicts with other libraries.
        //ImGui::InputText(name.data(), &s, ImGuiInputTextFlags_CallbackResize);
    }


    // *********************************************** UTILITY FUNCTIONS IMGUI DRAW ******************************


    auto EditorGUI::Startup() -> void
    {
        auto e1 = context->CreateEntity();
        context->RegisterToPhysics(e1, 1.0f);
        context->RegisterToRenderer(e1);
        e1.Emplace<scene::TagComponent>("Square");
    }

	auto EditorGUI::RenderGUI() -> void 
	{

    	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        ImGuiIO& io = ImGui::GetIO();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Scene manager");
        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | 
            ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
        
        if (ImGui::CollapsingHeader("Scene Hierarchy"))
        {
            EntityNode();
        }
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Properties");
        
        if (entity_selected != ecs::null_entity)
        {
            ShowComponents(entity_selected);
        }

        ImGui::End();
        ImGui::PopStyleVar();
	}


    auto EditorGUI::EntityNode() -> void
    {
        if (ImGui::TreeNode("Entities"))
        {
            auto& ecs_s = context->ECS();
            auto group = ecs_s.Group<scene::TagComponent>();
            auto view = group.View();
            ImGuiTreeNodeFlags node_flags = base_flags;
            node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            for (auto e : view)
            {
                auto& tag = ecs_s.Get<scene::TagComponent>(e);
                ImGui::TreeNodeEx((void*)(e), node_flags, tag.name.c_str());
                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                {
                    entity_selected = e;
                }
            }

            ImGui::TreePop();
        }
    }


    auto EditorGUI::ShowComponents(ecs::entity_t e) -> void
    {
        using namespace render;
        using namespace scene;

        auto entity = context->CreateEntityFromID(e);

        ShowComponent<TagComponent>("Tag", entity, [](TagComponent& t)
            {
                DrawText("TagName", t.name);
            });

        ShowComponent<TransformComponent>("Transform", entity, [](TransformComponent& t)
            {
                DrawVec3d("Position", t.position);
                DrawFloat("Rotation", t.rotation);
                DrawVec3d("Scale", t.scale);
            });
    }
} // namespace gargantua::editor