/*
* editor/editor_gui.cpp
*/

module;

#include <imgui.h>
#include <imgui_internal.h>
//#include <misc/cpp/imgui_stdlib.h>

#include <gargantua/log/logger_macro.hpp>

module gargantua.editor.editor_gui;

import <ranges>;

#define MAX_TEXT_LEN 24


namespace gargantua::editor
{
    // *********************************************** UTILITY FUNCTIONS IMGUI DRAW ******************************
    
    static auto DrawFloatControl(std::string_view name, f32& f, const f32 min = -3.0f, const f32 max = 3.0f) -> void
    {
        //ImGui::PushID(name.data());

        ImGui::DragFloat(name.data(), &f, 0.01f, min, max);
    }
    
    static auto DrawVec3dControl(std::string_view name, math::Vec3df& v, const f32 min = 0.0f, 
        const f32 max = 10.0f,
        const f32 reset_value = 0.0f, const f32 column_width = 100.0f) -> void
    {
        ImGuiIO& io = ImGui::GetIO();
        auto bold_font = io.Fonts->Fonts[0];
        
        
        // TEMPORARY, this avoid to have different vectors binded to the same "slide", because we assigned 
        // ##X, ##Y, ##Z as names.
        ImGui::PushID(name.data());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, column_width);
        ImGui::Text(name.data());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0 , 0 });

        // From imgui
        f32 line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 button_size = { line_height + 3.0f, line_height };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(bold_font);
        if (ImGui::Button("X", button_size))
        {
            v.x = reset_value;
        }
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##X", &v.x, 0.1f, min, max);
        ImGui::PopItemWidth();
        ImGui::SameLine();


        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushFont(bold_font);
        if (ImGui::Button("Y", button_size))
        {
            v.y = reset_value;
        }
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &v.y, 0.1f, min, max);
        ImGui::PopItemWidth();
        ImGui::SameLine();


        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.25f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushFont(bold_font);
        if (ImGui::Button("Z", button_size))
        {
            v.z = reset_value;
        }
        ImGui::PopFont();
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &v.z, 0.1f, min, max);
        ImGui::PopItemWidth();
        

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
        //ImGui::DragFloat3(name.data(), &v.x, 0.01f, -3.0f, 3.0f);
    }

    static auto DrawText(std::string_view name, std::string& s) -> void
    {
        char text[MAX_TEXT_LEN] = {};
        s.copy(text, MAX_TEXT_LEN);
        ImGui::PushItemWidth(MAX_TEXT_LEN * 5);
        if (ImGui::InputText(name.data(), text, MAX_TEXT_LEN))
        {
            s = text;
        }
        ImGui::PopItemWidth();

        // Impossible to use with misc/..., error in building for conflicts with other libraries.
        //ImGui::InputText(name.data(), &s, ImGuiInputTextFlags_CallbackResize);
    }


    // *********************************************** UTILITY FUNCTIONS IMGUI DRAW ******************************


    auto EditorGUI::Startup() -> void
    {
        using namespace physics2d;
        auto e1 = context->CreateEntity();
        context->RegisterToPhysics(e1, 0.5f, 0.5f, {1.0f, 1.0f});
        context->RegisterToRenderer(e1);
        e1.Emplace<scene::TagComponent>("Square");
        e1.Get<RigidBodyComponent>().restituition = 0.5f;
        //e1.Get<VelocityComponent>().v.x += 2.0f;
        //e1.Get<AngularVelocityComponent>().omega += 2.0f;

        /*auto e2 = context->CreateEntity();
        
        context->RegisterToPhysics(e2, 1.0f, {15.0f, 1.0f});
        context->RegisterToRenderer(e2);
        e2.Emplace<scene::TagComponent>("Square floor");
        e2.Get<MassComponent>().InfiniteMass();
        e2.Get<PositionComponent>().p = { 0.0f, -3.0f };*/
    }

	auto EditorGUI::RenderGUI() -> void 
	{
    	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        UISceneManager();
        UIProperties();
        UIToolbar();
	}


    auto EditorGUI::EntityNode() -> void
    {
        // We can't delete an entity inside the for each because the view would be not valid anymore.
        // So we need to "save" the current entity to be deleted and do the job after the for each.
        scene::Entity entity_to_be_deleted;
        if (ImGui::TreeNode("Entities"))
        {
            // TODO: maybe it's not necessary to do this transformation?
            auto& ecs_s = context->ECS();
            auto entities_view = context->GetEntities() | 
                std::views::transform([&](auto e)
                    {
                        return scene::Entity{e, context};
                    });
            
            
            for (auto e : entities_view)
            {
                const ImGuiTreeNodeFlags node_flags = ((entity_selected == e) ? ImGuiTreeNodeFlags_Selected : 0) | 
                    ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
                //node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

                std::string_view tag;
                if (e.Has<scene::TagComponent>())
                {
                    tag = e.Get<scene::TagComponent>().name;
                    
                    // TODO: Do not display the entity associated with the camera
                    // editor because in case of delete the editor crashes.
                    if (tag == "Editor")
                    {
                        continue;
                    }
                }
                else
                {
                    tag = "Entity";
                }

                // TODO: Is this popup necessary? Maybe it's better a list of entities without
                // treenode? 
                if (ImGui::TreeNodeEx((void*)(e.ID()), node_flags, tag.data()))
                {
                    ImGui::TreePop();
                }
                

                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                {
                    entity_selected = e;
                }

                // Right click on an entity to open a popup for delete.
                if (ImGui::BeginPopupContextItem())
                {
                    if (ImGui::MenuItem("Delete entity"))
                    {
                        entity_to_be_deleted = e;
                        entity_selected = {};
                    }
                    ImGui::EndPopup();
                }
            }

            ImGui::TreePop();
        
            entity_to_be_deleted.Destroy();
        }
    }


    auto EditorGUI::AddComponentNode() -> void
    {
        if (ImGui::MenuItem("Tag"))
        {
            entity_selected.Emplace<scene::TagComponent>();
            ImGui::CloseCurrentPopup();
        }
        else if (ImGui::MenuItem("Transform"))
        {
            entity_selected.Emplace<render::TransformComponent>();
            ImGui::CloseCurrentPopup();
        }
        else if (ImGui::MenuItem("Texture"))
        {
            entity_selected.Emplace<render::TextureComponent>();
            ImGui::CloseCurrentPopup();
        }
        else if (ImGui::MenuItem("Physics"))
        {
            context->RegisterToPhysics(entity_selected, 0.5f, 0.5f, { 1.0f, 1.0f });
            ImGui::CloseCurrentPopup();
        }
    }


    auto EditorGUI::ShowComponents(scene::Entity entity) -> void
    {
        using namespace render;
        using namespace scene;

        //static ImGuiComboFlags flags = 0;
        //ImGui::CheckboxFlags("ImGuiComboFlags_PopupAlignLeft", &flags, ImGuiComboFlags_PopupAlignLeft);

        ShowComponent<TagComponent>("Tag", entity, [](TagComponent& t)
            {
                DrawText("##Tag", t.name);
            });


        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add component"))
        {
            ImGui::OpenPopup("add_component");
        }
        if (ImGui::BeginPopup("add_component"))
        {
            AddComponentNode();
            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();


        ShowComponent<TransformComponent>("Transform", entity, [](TransformComponent& t)
            {
                DrawVec3dControl("Position", t.position, -10.f, 10.0f);
                DrawFloatControl("Rotation", t.rotation);
                DrawVec3dControl("Scale", t.scale, 0.5f, 10.0f, 1.0f);
            });

        ShowComponent<TextureComponent>("Texture", entity, [=](TextureComponent& t)
            {
                // TODO: create a new texture with a name
                // Can be loaded from a file or created using the color palette.

                ImGui::ColorEdit4("Color", reinterpret_cast<f32*>(&t.color));
                ImGui::DragFloat("Tiling factor", &t.tiling_factor, 0.1f, 0.0f, 100.0f);
            });

        ShowComponent<CameraComponent>("Camera", entity, [](CameraComponent& c)
            {

            });


        ShowPhysicsComponents(entity);
    }


    auto EditorGUI::ShowPhysicsComponents(scene::Entity entity) -> void
    {
        using namespace physics2d;
        ShowComponent<MassComponent>("Mass", entity, [](MassComponent& c)
            {
                f32 m = c.m;
                ImGui::SliderFloat("Mass", &m, 0.0f, 100.0f);
                c.SetMass(m);
            });

        ShowComponent<RigidBodyComponent>("RigidBody", entity, [](RigidBodyComponent& b)
            {
                ImGui::SliderFloat("Static friction", &b.static_friction, 0.01f, 10.0f);
                ImGui::SliderFloat("Dynamic friction", &b.dynamic_friction, 0.01f, 10.0f);
                ImGui::SliderFloat("Restituition", &b.restituition, 0.01f, 10.0f);
            });
    }


    auto EditorGUI::UISceneManager() -> void
    {
        //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Scene manager");
        /*static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow |
            ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;*/

        if (ImGui::CollapsingHeader("Scene Hierarchy"))
        {
            EntityNode();
        }


        // Right click on a blank space in scene manager open a popup for the creation of a new entity.
        if (ImGui::BeginPopupContextWindow(0, ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
        {
            if (ImGui::MenuItem("Create empty entity"))
            {
                context->CreateEntity("Empty entity");
            }

            ImGui::EndPopup();
        }


        ImGui::End();
        //ImGui::PopStyleVar();
    }

    auto EditorGUI::UIProperties() -> void
    {
        //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Properties");

        if (entity_selected.IsValid())
        {
            ShowComponents(entity_selected);
        }

        ImGui::End();
        //ImGui::PopStyleVar();
    }



    auto EditorGUI::UIToolbar() -> void
    {
        ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        if (ImGui::Button("Play"))
        {   
            context->SimulationMode();
        }

        if (ImGui::Button("Stop"))
        {
            context->EditorMode();
        }

        ImGui::End();
    }
} // namespace gargantua::editor