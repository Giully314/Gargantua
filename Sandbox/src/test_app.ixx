export module sandobox.testapp;

import gargantua;

using namespace gargantua;

export class TestApplication final : public app::Application
{
public:
	auto Run(const time::TimeStep& ts) -> app::ApplicationState override
	{
		const auto position = math::Vec2df{ 0.0f, 0.0f };
		const auto size = math::Vec2df{ 1.0f, 1.0f };
		const auto color = math::Vec4df{ 1.0f, 1.0f, 1.0f, 1.0f };


		auto& r = render::RendererSystem::Instance();
		r.BeginScene(camera.GetViewProjection());
		r.DrawQuad(position, size, color);
		r.EndScene();
		
		return app::ApplicationState::Running;
	}


private:
	render::OrthoCamera camera{ -1.0f, -1.0f, 1.0f, 1.0f };
};