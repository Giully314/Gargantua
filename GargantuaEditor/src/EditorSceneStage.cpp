/*
EditorSceneStage.cpp
*/
#include "EditorSceneStage.hpp"


#include <Gargantua/Renderer/RendererCommand.hpp>
#include <Gargantua/Renderer/Utility.hpp>

#include <Gargantua/Math/Vec4d.hpp>

#include <Gargantua/Event/WindowEvents.hpp>
#include <Gargantua/Event/MouseEvents.hpp>
#include <Gargantua/Event/ImGuiEvents.hpp>

#include <Gargantua/Systems/ResourceSystem.hpp>

#include <Gargantua/Core/EngineLogger.hpp>


namespace Gargantua
{
    namespace Editor
    {
        //Equality between a Math::Vec2di and a ImGui vec
        static bool VectorsEquality(const Math::Vec2di& v1, const ImVec2& v2)
        {
            return v1.x == v2.x && v1.y == v2.y;
        }


        void EditorSceneStage::Start()
        {
            const real_t aspect_ratio = 1280.0f / 720.0f;
            controller.CreateCamera(aspect_ratio);

            systems.engine_event_sys->RegisterListener<Event::ImGuiPanelResizeEvent>(
                [this](const Event::BaseEvent& e)
                {
                    const Event::ImGuiPanelResizeEvent& pre = static_cast<const Event::ImGuiPanelResizeEvent&>(e);
                    controller.CreateCamera((real_t)pre.new_width / (real_t)pre.new_height);
                });


            systems.engine_event_sys->RegisterListener<Event::MouseWheelScrollEvent>(
                [this](const Event::BaseEvent& e)
                {
                    const Event::MouseWheelScrollEvent& me = static_cast<const Event::MouseWheelScrollEvent&>(e);

                    controller.ZoomLevelOffset(me.y_offset);
                }
            );


            systems.engine_event_sys->RegisterListener<Event::ImGuiPanelResizeEvent>(
                [this](const Event::BaseEvent& e)
                {
                    const Event::ImGuiPanelResizeEvent& pre = static_cast<const Event::ImGuiPanelResizeEvent&>(e);

                    systems.renderer2d_sys->ResizeFrameBuffer(pre.new_width, pre.new_height);
                });


            player.color = { 1, 0, 1, 1 };

            player2.position.x = 5;
            player2.color = { 0, 1, 0, 1 };

            background.position = { -1, -1 };
            background.scale = { 25, 15 };

            background.texture = Systems::ResourceSystem::LoadSharedTexture2d("resources/test/BG.png");
        }


        void EditorSceneStage::End()
        {

        }


        void EditorSceneStage::Execute(const Time::TimeStep& ts)
        {
            player.rotation += (real_t)(5 * ts.GetInSec());

            controller.Update(ts);
            systems.renderer2d_sys->BeginScene(controller.GetCamera());

            systems.renderer2d_sys->DrawQuad(background.position, background.scale, *background.texture);
            systems.renderer2d_sys->DrawRotatedQuad(player.position, player.scale, player.rotation, player.color);
            systems.renderer2d_sys->DrawQuad(player2.position, player2.scale, player2.color);

            systems.renderer2d_sys->EndScene();
        }

        void EditorSceneStage::RenderGUI()
        {
            ImGuiIO& io = ImGui::GetIO(); 
            
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
            ImGui::Begin("Scene2d");
            

            //This blocks the keyboard and mouse if the panel is not both focused and hovered.
            //It also reset the state of the keyboard to avoid bugs if the focus is changed while a key is pressed.
            systems.engine_event_sys->BlockInputEvents(!(ImGui::IsWindowFocused() && ImGui::IsWindowHovered()));
            if (!(ImGui::IsWindowFocused() && ImGui::IsWindowHovered()))
            {
                Systems::InputSystem::ResetState();
            }

            ImVec2 viewport_panel = ImGui::GetContentRegionAvail();

            if (!VectorsEquality(scene_panel_size, viewport_panel))
            {
                scene_panel_size.x = (integer_t)viewport_panel.x;
                scene_panel_size.y = (integer_t)viewport_panel.y;

                //Register event
                systems.engine_event_sys->RegisterEvent<Event::ImGuiPanelResizeEvent>(scene_panel_size.x, scene_panel_size.y);
            }

            
            unsigned int fbid = systems.renderer2d_sys->GetFrameBuffer().GetColorBufferId();
            auto& fb = systems.renderer2d_sys->GetFrameBuffer();
            ImGui::Image((void*)fbid, { (float)fb.GetWidth(), (float)fb.GetHeight() }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

            
            ImGui::End();
            ImGui::PopStyleVar();


            ImGui::Begin("Entity setup");

            ImGui::ColorEdit4("Square color", (float*)&player.color);
            ImGui::SliderAngle("Rotation", &player.rotation);


            ImGui::End();
        }

    } //namespace Editor
} //namespace Gargantua