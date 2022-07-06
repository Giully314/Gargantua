/*
EditorSceneStage.cpp

OVERVIEW:
    For now most of the code is for testing the features of the editor, so there isn't so much to say.
*/
#include "EditorSceneStage.hpp"


#include <Gargantua/Renderer/RendererCommand.hpp>
#include <Gargantua/Renderer/Utility.hpp>


#include <Gargantua/Math/Vec4d.hpp>
#include <Gargantua/Math/MathFunctions.hpp>

#include <Gargantua/Input/KeyCodes.hpp>

#include <Gargantua/Event/WindowEvents.hpp>
#include <Gargantua/Event/MouseEvents.hpp>
#include <Gargantua/Event/ImGuiEvents.hpp>

#include <Gargantua/Systems/ResourceSystem.hpp>

#include <Gargantua/Core/EngineLogger.hpp>


#include <Gargantua/Settings.hpp>


namespace Gargantua
{
    namespace Editor
    {
        //Equality between a Math::Vec2di and a ImGui vec
        static bool VectorsEquality(const Math::Vec2di& v1, const ImVec2& v2)
        {
            return v1.x == v2.x && v1.y == v2.y;
        }


        void EditorSceneStage::RegisterEventListeners()
        {
            systems.engine_event_sys->RegisterListener<Event::ImGuiPanelResizeEvent>(
                [this](const Event::BaseEvent& e)
                {
                    const Event::ImGuiPanelResizeEvent& pre = static_cast<const Event::ImGuiPanelResizeEvent&>(e);
                    

                    auto& c = scene->GetComponent<Renderer::OrthoCameraComponent>(camera);
                    c.aspect_ratio = (real_t)pre.new_width / (real_t)pre.new_height;
                    c.projection = Math::Projection::Orthographic(-c.aspect_ratio * c.zoom_level,
                    -c.zoom_level, c.aspect_ratio * c.zoom_level, c.zoom_level);
                });


            systems.engine_event_sys->RegisterListener<Event::MouseWheelScrollEvent>(
                [this](const Event::BaseEvent& e)
                {
                    const Event::MouseWheelScrollEvent& me = static_cast<const Event::MouseWheelScrollEvent&>(e);

                    auto& c = scene->GetComponent<Renderer::OrthoCameraComponent>(camera);
                    c.zoom_level -= me.y_offset * 0.25f;
                    c.zoom_level = std::max(c.zoom_level, 0.5f);
                    c.projection = Math::Projection::Orthographic(-c.aspect_ratio * c.zoom_level,
                        -c.zoom_level, c.aspect_ratio * c.zoom_level, c.zoom_level);
                }
            );


            systems.engine_event_sys->RegisterListener<Event::ImGuiPanelResizeEvent>(
                [this](const Event::BaseEvent& e)
                {
                    const Event::ImGuiPanelResizeEvent& pre = static_cast<const Event::ImGuiPanelResizeEvent&>(e);

                    systems.renderer2d_sys->ResizeFrameBuffer(pre.new_width, pre.new_height);
                });
        }


        static void SetOrthoCameraProjection(Renderer::OrthoCameraComponent& c, real_t aspect_ratio, real_t zoom)
        {
            c.aspect_ratio = aspect_ratio;
            c.zoom_level = zoom;
            c.projection = Math::Projection::Orthographic(-c.aspect_ratio * c.zoom_level,
                -c.zoom_level, c.aspect_ratio * c.zoom_level, c.zoom_level);
        }


        void EditorSceneStage::Start()
        {
            using namespace Physics;

            systems.time_sys->SetUpdatePerSecond(80.0f);

            const real_t aspect_ratio = 1280.0f / 720.0f;
            const real_t zoom_level = 5.0f;

            RegisterEventListeners();


            e1 = scene->CreateEntity();
            scene->CreatePlayerEntity(e1);
            auto& in_p = scene->GetComponent<Input::MoveActionComponent>(e1);
            const real_t vp = 10.0f;
            in_p.up.first = Input::Key::UP;
            in_p.up.second = { 0.0f, 30.0f };
            in_p.down.first = Input::Key::DOWN;
            in_p.down.second = { 0.0f, -vp };
            in_p.left.first = Input::Key::LEFT;
            in_p.left.second = { -vp, 0.0f };
            in_p.right.first = Input::Key::RIGHT;
            in_p.right.second = { vp, 0.0f };

            e2 = scene->CreateEntity();
            scene->CreateMotionEntity(e2);
            scene->CreateCollisionEntity(e2);
            scene->CreateRendererEntity(e2);

            ground = scene->CreateEntity();
            scene->CreateMotionEntity(ground);
            scene->CreateCollisionEntity(ground);
            scene->CreateRendererEntity(ground);

            camera = scene->CreateEntity();
            scene->CreateOrthoCamera(camera);
            scene->CreateInputActionEntity(camera);
            scene->SetCamera(camera);

            auto& cam_proj = scene->GetComponent<Renderer::OrthoCameraComponent>(camera);
            cam_proj.projection = Math::Projection::Orthographic(-aspect_ratio * zoom_level,
                -zoom_level, aspect_ratio * zoom_level, zoom_level);
            
            PositionComponent& ground_p = scene->GetComponent<PositionComponent>(ground);
            ground_p.position = { 0.0f, -3.0f };


            auto& p1 = scene->GetComponent<PositionComponent>(e1);
            p1.position = { -3.0f, -0.0f };
            auto& m1 = scene->GetComponent<MassComponent>(e1);
            m1.inv_mass = 1.0f / 50.0f;

            auto& cr1 = scene->GetComponent<CoefficientRestituitionComponent>(e1);
            cr1.e = 0.95f;

            auto& in = scene->GetComponent<Input::MoveActionComponent>(camera);
            const real_t v = 1.0f;
            in.up.first = Input::Key::W;
            in.up.second = { 0.0f, v };
            in.down.first = Input::Key::S;
            in.down.second = { 0.0f, -v };
            in.left.first = Input::Key::A;
            in.left.second = { -v, 0.0f };
            in.right.first = Input::Key::D;
            in.right.second = { v, 0.0f };
            
            
            auto& p2 = scene->GetComponent<PositionComponent>(e2);
            p2.position = { 0.5f, 1.0f };
            auto& m2 = scene->GetComponent<MassComponent>(e2);
            m2.inv_mass = 1.0f / 30.0f;

            auto& cr2 = scene->GetComponent<CoefficientRestituitionComponent>(e2);
            cr2.e = 0.95f;


            auto& scale_ground = scene->GetComponent<ScaleComponent>(ground);
            scale_ground.scale = {10.0f, 2.0f};
        }


        void EditorSceneStage::End()
        {

        }


        void EditorSceneStage::Execute(const Time::TimeStep& ts)
        {
            scene->RunScene(ts);
        }


        void EditorSceneStage::RenderGUI()
        {
            ImGuiIO& io = ImGui::GetIO(); 
            
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
            ImGui::Begin("Scene2d");
            

            //This blocks the keyboard and mouse if the panel is not both focused and hovered.
            //It also reset the state of the keyboard to avoid bugs if the focus is changed while a key is pressed.
            if (!(ImGui::IsWindowFocused() && ImGui::IsWindowHovered()))
            {
                systems.engine_event_sys->BlockInputEvents(true);
                Systems::InputSystem::ResetState();
            }
            else
            {
                systems.engine_event_sys->BlockInputEvents(false);
            }

            ImVec2 viewport_panel = ImGui::GetContentRegionAvail();

            if (!VectorsEquality(scene_panel_size, viewport_panel))
            {
                scene_panel_size.x = (integer_t)viewport_panel.x;
                scene_panel_size.y = (integer_t)viewport_panel.y;

                systems.engine_event_sys->RegisterEvent<Event::ImGuiPanelResizeEvent>(scene_panel_size.x, scene_panel_size.y);
            }

            
            unsigned int fbid = systems.renderer2d_sys->GetFrameBuffer().GetColorBufferId();
            auto& fb = systems.renderer2d_sys->GetFrameBuffer();
            ImGui::Image((void*)fbid, { (float)fb.GetWidth(), (float)fb.GetHeight() }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

            
            ImGui::End();
            ImGui::PopStyleVar();
        }

    } //namespace Editor
} //namespace Gargantua