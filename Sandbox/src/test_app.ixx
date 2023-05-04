module;

#include <glad/glad.h>

export module sandbox.test_app;

import gargantua.types;
import gargantua.app.application;
import gargantua.render.render;
import gargantua.render.renderer_command;
import gargantua.math.vector;
using namespace gargantua;

import <span>;

export
class TestApp : public app::Application
{
public:
	auto Startup() -> void override
	{
		render::RendererCommand::SetClearColor(math::Vec4df{ 0.0f, 0.0f, 0.0f, 1.0f });
		texture = CreateSharedRes<render::Texture2d>();
		texture->Load("src/assets/e.jpg");
	}


	auto Begin() -> void override
	{
		render::Renderer2dSystem::Instance().BeginScene(camera.GetViewProjection());
	}


	auto End() -> void override
	{
		render::Renderer2dSystem::Instance().EndScene();
	}

	auto Run() -> app::ApplicationState override
	{
		using namespace math;
		camera.ComputeViewProjection();

		Vec2df position{ 0.0f, 0.0f };
		Vec4df color{ 0.0f, 1.0f, 1.0f, 1.0f };
		Vec2df size{ 1, 1 };
		Vec2df position1{ 1.0f, 1.0f };
		Vec4df color1{ 0.0f, 1.0f, 1.0f, 1.0f };
		Vec2df size1{ 1, 1 };

		Vec2df position2{ -1.0f, -1.0f };
		Vec4df color2{ 0.0f, 0.0f, 1.0f, 1.0f };
		Vec2df size2{ 2, 1 };
	
		
		auto& renderer = render::Renderer2dSystem::Instance();
		renderer.DrawRotatedQuad(position1, size1, 1.0f, color1);
		renderer.DrawQuad(position2, size2, color2);
		renderer.DrawQuad(position, size, texture);

		return app::ApplicationState::Running;
	}

private:
	render::OrthoCamera camera{ 0.0f, 0.0f, 720.0f, 480.0f };
	shared_res<render::Texture2d> texture;
};