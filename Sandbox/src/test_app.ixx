//module;
//
//#include <glad/glad.h>
//#include <gargantua/log/logger_macro.hpp>
//export module sandbox.test_app;
//
//import gargantua.types;
//import gargantua.app.application;
//import gargantua.render.render;
//import gargantua.math.vector;
//import gargantua.platform.platform;
//import gargantua.time.time_step;
//import gargantua.log.logger_system;
//import gargantua.ecs.ecs;
//import gargantua.physics.physics;
//using namespace gargantua;
//
//import <span>;
//
//
//class CameraController
//{
//public:
//	CameraController() = default;
//	CameraController(f32 aspect_ratio_) : aspect_ratio(aspect_ratio_), zoom_level(1.0f),
//		velocity(1.0f), camera(-aspect_ratio * zoom_level, -zoom_level, aspect_ratio* zoom_level,
//			zoom_level)
//	{
//
//	}
//
//	auto RegisterToEvents() -> void
//	{
//		using namespace platform;
//		auto& ev = PlatformEventDispatcher::Instance();
//
//		ev.RegisterListener<MouseWheelScrollEvent>([this](const MouseWheelScrollEvent& e)
//			{
//				zoom_level -= e.y_offset * 0.1f;
//				camera.SetProjection(-aspect_ratio * zoom_level, -zoom_level, aspect_ratio * zoom_level,
//					zoom_level);
//
//			});
//
//		ev.RegisterListener<WindowResizeEvent>([this](const WindowResizeEvent& e)
//			{
//				aspect_ratio = static_cast<f32>(e.new_width) / e.new_height;
//				camera.SetProjection(-aspect_ratio * zoom_level, -zoom_level, aspect_ratio * zoom_level,
//					zoom_level);
//			});
//	}
//
//	auto Update(const time::TimeStep& ts) -> void
//	{
//		using namespace platform;
//		auto& inp = InputSystem::Instance();
//		auto pos = camera.GetPosition();
//		auto rot = camera.GetRotation();
//		auto upd = velocity * static_cast<f32>(ts.GetInSec());
//
//		if (inp.IsPressed(Key::W))
//		{
//			pos.y += upd;
//		}
//		if (inp.IsPressed(Key::A))
//		{
//			pos.x -= upd;
//		}
//		if (inp.IsPressed(Key::S))
//		{
//			pos.y -= upd;
//		}
//		if (inp.IsPressed(Key::D))
//		{
//			pos.x += upd;
//		}
//
//
//		if (inp.IsPressed(Key::RIGHT))
//		{
//			rot -= upd;
//		}
//		if (inp.IsPressed(Key::LEFT))
//		{
//			rot += upd;
//		}
//		
//		camera.SetPositionRotation(pos, rot);
//	}
//
//public:
//	f32 aspect_ratio = 16.0f / 10.0f;
//	f32 zoom_level = 1.0f;
//	const f32 velocity = 1.0f;
//	render::OrthoCamera camera{ -1.0f, -1.0f, 1.0f, 1.0f };
//};
//
//
//export
//class TestApp : public app::Application
//{
//public:
//	auto Startup() -> void override
//	{
//		using namespace physics;
//		render::RendererCommand::SetClearColor(math::Vec4df{ 0.0f, 0.0f, 0.0f, 1.0f });
//		texture = CreateSharedRes<render::Texture2d>();
//		texture->Load("src/assets/e.jpg");
//		
//		sheet = CreateSharedRes<render::Texture2d>();
//		sheet->Load("src/assets/sheet2.png");
//
//		sub1 = CreateSharedRes<render::SubTexture2d>(sheet, math::Vec2df{ 0, 0 }, math::Vec2df{ 129, 149 });
//
//		controller.camera.SetPosition({ 0.0f, 0.0f, -0.5f });
//		controller.RegisterToEvents();
//
//		auto& ecs_s = ecs::ECSSystem::Instance();
//
//		e1 = ecs_s.Create();
//		PhysicsSystem::Instance().Register(e1, 10.0f);
//		auto& f = ecs_s.Get<Force>(e1);
//		f.f = math::Vec2df{ 3.0f, 0.0f };
//	}
//
//
//	auto Begin() -> void override
//	{
//		//controller.camera.ComputeViewProjection();
//		render::Renderer2dSystem::Instance().BeginScene(controller.camera.GetViewProjection());
//	}
//
//
//	auto End() -> void override
//	{
//		render::Renderer2dSystem::Instance().EndScene();
//	}
//
//	auto Run(const time::TimeStep& ts) -> app::ApplicationState override
//	{
//		using namespace physics;
//		auto& ecs_s = ecs::ECSSystem::Instance();
//		controller.Update(ts);
//
//		PhysicsSystem::Instance().Run(ts);
//		
//		auto& p = ecs_s.Get<Position>(e1);
//
//		using namespace math;
//
//		Vec2df position{ 0.0f, 0.0f };
//		Vec4df color{ 0.0f, 1.0f, 1.0f, 1.0f };
//		Vec2df size{ 1, 1 };
//		Vec2df position1{ 1.0f, 1.0f };
//		Vec4df color1{ 0.0f, 1.0f, 1.0f, 1.0f };
//		Vec2df size1{ 1, 1 };
//
//		Vec2df position2{ -1.0f, -1.0f };
//		Vec4df color2{ 0.0f, 0.0f, 1.0f, 1.0f };
//		Vec2df size2{ 2, 1 };
//	
//		
//		auto& renderer = render::Renderer2dSystem::Instance();
//		renderer.DrawRotatedQuad(p.p, size1, 1.0f, color1);
//		renderer.DrawQuad(position2, size2, color2);
//		//renderer.DrawQuad(position, size, texture);
//		renderer.DrawQuad(position, size, *sub1);
//
//		return app::ApplicationState::Running;
//	}
//
//private:
//	/*render::OrthoCamera camera{ -1.0f, -1.0f, 1.0f, 1.0f };*/
//	CameraController controller;
//	shared_res<render::Texture2d> texture;
//	shared_res<render::Texture2d> sheet;
//	shared_res<render::SubTexture2d> sub1;
//	//render::SubTexture2d sub2;
//
//	ecs::entity_t e1;
//};