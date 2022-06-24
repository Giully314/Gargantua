/*
Sandbox/src/App.cpp
*/
#include "App.hpp"

#include <glad/glad.h>

#include "Stages.hpp"



namespace Sandbox
{
	void App::Start() 
	{
		auto program = systems.shader_sys->CreateProgram("BasicTransform.vert", "BasicColorTexture.frag");
		auto fb_program = systems.shader_sys->CreateProgram("ScreenTransform.vert", "ScreenColor.frag");
		
		systems.renderer2d_sys->SetProgram(program);
		systems.renderer2d_sys->SetFBProgram(fb_program);

		pipeline.AddStage<RenderTestStage>(systems);

		pipeline.Start();
		//pipeline.AddStage<TestStage>(systems);
	}
} //namespace Sandbox



//
//#include "Gargantua/Engine.hpp"
//#include "Gargantua/Types.hpp"
//
//
//#include "Gargantua/Core/EngineLogger.hpp"
//#include "Gargantua/Core/Application.hpp"
//#include "Gargantua/Core/Stage.hpp"
//#include "Gargantua/Core/EngineSystems.hpp"
//
//#include "Gargantua/ECS/Types.hpp"
//
//#include "Gargantua/Time/TimeStep.hpp"
//
//#include "Gargantua/Renderer/VertexBuffer.hpp"
//#include "Gargantua/Renderer/ElementBuffer.hpp"
//#include "Gargantua/Renderer/VertexArray.hpp"
//#include "Gargantua/Renderer/Shader.hpp"
//#include "Gargantua/Renderer/Program.hpp"
//#include "Gargantua/Renderer/Texture2d.hpp"
//#include "Gargantua/Renderer/Types.hpp"
//#include "Gargantua/Renderer/OrthoCamera.hpp"
//#include "Gargantua/Renderer/OrthoCameraController.hpp"
//#include "Gargantua/Renderer/Utility.hpp"
//
//#include "Gargantua/Physics/PhysicsComponents.hpp"
//#include "Gargantua/Physics/NewtonianSystem.hpp"
//
//#include "Gargantua/Math/Vec4d.hpp"
//#include "Gargantua/Math/Functions.hpp"
//
//#include "Gargantua/Event/WindowEvents.hpp"
//
//#include <imgui.h>
//
//
//#include <iostream>
//#include <numbers>
//
//using namespace Gargantua;
//
//#define POSITION 0
//#define TEXTURE 1
//
//constexpr unsigned int WIDTH = 1280;
//constexpr unsigned int HEIGHT = 720;




//class TestStage : public Gargantua::Core::Stage
//{
//public:
//	TestStage(Core::EngineSystems systems_) : Gargantua::Core::Stage("TestStage"), systems(std::move(systems_))
//	{
//		auto& ecs = systems.ecs_sys;
//		
//		ship = ecs->Create();
//		ecs->Register<Renderer::SpriteComponent>(ship, Renderer::Utility::CreateTX2d("resources/test/Plane/Fly (1).png"));
//		ecs->Register<Physics::TransformComponent>(ship);
//
//		ecs->Register<Physics::NewtonianSystem>(ship);
//
//
//		auto& p = ecs->Get<Physics::TransformComponent>(ship);
//		GRG_CORE_INFO("{}", p.position.ToString());
//
//
//		real_t aspect_ratio = (real_t)WIDTH / (real_t)HEIGHT;
//		real_t cam_value = 5.0f;
//		real_t b = -cam_value;
//		real_t t = cam_value;
//		real_t r = cam_value * aspect_ratio;
//		real_t l = -r;
//		ortho_camera = ecs->Create();
//		ecs->Register<Renderer::OrthoCameraComponent>(ortho_camera, l, b, r, t);
//		
//
//		program = systems.shader_sys->CreateProgram("BasicTransform.vert", "BasicColorTexture.frag");
//		auto fb_program = systems.shader_sys->CreateProgram("ScreenTransform.vert", "ScreenColor.frag");
//
//		camera = Renderer::Utility::CreateOrtho(WIDTH, HEIGHT);
//		controller.SetCamera(camera.get());
//
//		auto s = systems.engine_event_sys;
//		s->GetEventListenerManager()->RegisterListener<Event::WindowResizeEvent>(
//			[this](const Event::BaseEvent& e)
//			{
//				const Event::WindowResizeEvent& we = static_cast<const Event::WindowResizeEvent&>(e);
//				camera = Renderer::Utility::CreateOrtho(we.new_width, we.new_height);
//				controller.SetCamera(camera.get());
//			});	
//
//		systems.renderer2d_sys->SetProgram(program);
//		systems.renderer2d_sys->SetFBProgram(fb_program);
//	}
//
//	~TestStage()
//	{
//		program->Destroy();
//	}
//
//
//	void Start() override
//	{
//		//systems.renderer2d_sys->BeginScene(*camera);
//		auto& c = systems.ecs_sys->Get<Renderer::OrthoCameraComponent>(ortho_camera);
//		systems.renderer2d_sys->BeginScene(c.proj_view);
//	}
//
//	void End() override
//	{
//		systems.renderer2d_sys->EndScene();
//	}
//
//	void Execute(const Gargantua::Time::TimeStep& ts) override 
//	{
//		//Math::Vec4df colors[128] = { Math::Vec4df{1.0f, 1.0f, 1.0f, 1.0f} };
//
//		natural_t colors[400] = { 0xffffffff };
//		std::fill_n(colors, 400, 0xffffffff);
//
//		//auto bg_transf = Math::Transform3d::Translate(Math::Vec3df{-5, 0, 0}) * Math::Transform3d::Scale(10.0f);
//		auto bg_transf = Math::Transform3d::Scale(Math::Vec3df{10, 5, 0});
//		auto s_scale = Math::Transform3d::Translate(Math::Vec3df{ 3, 3, 0 }) *  Math::Transform3d::Scale(1.0f);
//		controller.Update(ts);
//		
//		//Change the refence system from 0,0 located at the center of the screen to left up.
//
//		auto& t = systems.ecs_sys->Get<Physics::TransformComponent>(ship);
//		auto& s = systems.ecs_sys->Get<Renderer::SpriteComponent>(ship);
//		systems.renderer2d_sys->DrawRotatedQuad(t.position, t.scale, t.rotation, *s);
//
//		systems.renderer2d_sys->DrawQuad(Math::Vec2df{ 1, 1 }, Math::Vec2df{ 1, 1 }, Math::Vec4df{1.0f, 0.0f, 0.0f, 1.0f});
//		systems.renderer2d_sys->DrawRotatedQuad(Math::Vec2df{ 1, 1 }, Math::Vec2df{ 1, 1 }, 45.0f, Math::Vec4df{1.0f, 0.0f, 0.0f, 1.0f});
//		
//		systems.renderer2d_sys->DrawPixels(0, HEIGHT - 20, 20, 1, (void*)colors);
//	}
//
//
//	void RenderGUI() override
//	{
//		//ImGui::Text("CIAO COME STAI");
//		/*ImGui::Begin("Color setting");
//
//		ImGui::ColorEdit4("Color", &color[0]);
//		
//		ImGui::End();*/
//	}
//
//private:
//	ECS::Entity ship;
//	ECS::Entity ortho_camera;
//
//	SharedRes<Renderer::Shader> vert_shad;
//	SharedRes<Renderer::Shader> frag_shad;
//	SharedRes<Renderer::Program> program;
//
//	UniqueRes<Renderer::OrthoCamera> camera;
//	Renderer::OrthoCameraController controller;
//	
//	Math::Vec4df color;
//	Core::EngineSystems systems;
//};



//class Sandbox : public Gargantua::Core::Application
//{
//public:
//	void Start() override 
//	{
//		//Core::EngineLogger::Get()->SetLevel(Log::Level::info);
//		pipeline.AddStage<TestStage>(systems);
//	}
//	void Shutdown() override { }
//};



//int main()
//{
//	using namespace Gargantua;
//
//	/*Core::EngineLogger e;
//	
//	
//	Test::ComponentManagerTest test;
//	test.Run();*/
//
//	Gargantua::Engine e{ []() {return new Sandbox{}; }, WIDTH, HEIGHT };
//	e.Run();
//
//	return 0;
//}