#include <glad/glad.h>

#include "Gargantua/Engine.hpp"
#include "Gargantua/Types.hpp"


#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Core/Application.hpp"
#include "Gargantua/Core/Stage.hpp"
#include "Gargantua/Core/EngineSystems.hpp"


#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Renderer/VertexBuffer.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/VertexArray.hpp"
#include "Gargantua/Renderer/Shader.hpp"
#include "Gargantua/Renderer/Program.hpp"
#include "Gargantua/Renderer/Texture2d.hpp"
#include "Gargantua/Renderer/Types.hpp"
#include "Gargantua/Renderer/OrthoCamera.hpp"
#include "Gargantua/Renderer/OrthoCameraController.hpp"
#include "Gargantua/Renderer/Utility.hpp"

#include "Gargantua/Math/Vec4d.hpp"
#include "Gargantua/Math/Functions.hpp"

#include "Gargantua/Event/WindowEvents.hpp"

#include <imgui.h>

#include <iostream>
#include <numbers>

using namespace Gargantua;

#define POSITION 0
#define TEXTURE 1

constexpr unsigned int WIDTH = 1280;
constexpr unsigned int HEIGHT = 720;


/*
ONLY FOR TESTING.
*/
struct Mesh
{
	~Mesh()
	{
		if (texture)
		{
			texture->Destroy();
		}
	}

	UniqueRes<Renderer::Texture2d> texture;
};


class TestStage : public Gargantua::Core::Stage
{
public:
	TestStage(Core::EngineSystems systems_) : Gargantua::Core::Stage("TestStage"), systems(std::move(systems_))
	{
		//background.texture = Renderer::Utility::CreateTX2d("resources/test/BG.png");


		ship.texture = Renderer::Utility::CreateTX2d("resources/test/Plane/Fly (1).png");
	

		program = systems.shader_sys->CreateProgram("BasicTransform.vert", "BasicColorTexture.frag");
		auto fb_program = systems.shader_sys->CreateProgram("ScreenTransform.vert", "ScreenColor.frag");

		camera = Renderer::Utility::CreateOrtho(WIDTH, HEIGHT);
		controller.SetCamera(camera.get());

		auto s = systems.engine_event_sys;
		s->GetEventListenerSystem()->RegisterListener<Event::WindowResizeEvent>(
			[this](const Event::BaseEvent& e)
			{
				const Event::WindowResizeEvent& we = static_cast<const Event::WindowResizeEvent&>(e);
				camera = Renderer::Utility::CreateOrtho(we.new_width, we.new_height);
				controller.SetCamera(camera.get());
			});	

		systems.renderer2d_sys->SetProgram(program);
		systems.renderer2d_sys->SetFBProgram(fb_program);
	}

	~TestStage()
	{
		program->Destroy();
	}


	void Start() override
	{
		systems.renderer2d_sys->BeginScene(*camera);
	}

	void End() override
	{
		systems.renderer2d_sys->EndScene();
	}

	void Execute(const Gargantua::Time::TimeStep& ts) override 
	{
		//Math::Vec4df colors[128] = { Math::Vec4df{1.0f, 1.0f, 1.0f, 1.0f} };

		natural_t colors[400] = { 0xffffffff };
		std::fill_n(colors, 400, 0xffffffff);

		//auto bg_transf = Math::Transform3d::Translate(Math::Vec3df{-5, 0, 0}) * Math::Transform3d::Scale(10.0f);
		auto bg_transf = Math::Transform3d::Scale(Math::Vec3df{10, 5, 0});
		auto s_scale = Math::Transform3d::Translate(Math::Vec3df{ 3, 3, 0 }) *  Math::Transform3d::Scale(1.0f);
		controller.Update(ts);
		

		systems.renderer2d_sys->DrawQuad(Math::Vec2df{ 0, 0 }, Math::Vec2df{ 2, 2 }, *ship.texture);
		systems.renderer2d_sys->DrawQuad(Math::Vec2df{ 1, 1 }, Math::Vec2df{ 1, 1 }, Math::Vec4df{1.0f, 0.0f, 0.0f, 1.0f});
		systems.renderer2d_sys->DrawRotatedQuad(Math::Vec2df{ 1, 1 }, Math::Vec2df{ 1, 1 }, 45.0f, Math::Vec4df{1.0f, 0.0f, 0.0f, 1.0f});
		
		systems.renderer2d_sys->DrawPixels(0, HEIGHT - 20, 20, 1, (void*)colors);
	}


	void RenderGUI() override
	{
		//ImGui::Text("CIAO COME STAI");
		/*ImGui::Begin("Color setting");

		ImGui::ColorEdit4("Color", &color[0]);
		
		ImGui::End();*/
	}

private:
	Mesh ship;
	Mesh background;

	SharedRes<Renderer::Shader> vert_shad;
	SharedRes<Renderer::Shader> frag_shad;
	SharedRes<Renderer::Program> program;

	UniqueRes<Renderer::OrthoCamera> camera;
	Renderer::OrthoCameraController controller;
	
	Math::Vec4df color;
	Core::EngineSystems systems;
};



class Sandbox : public Gargantua::Core::Application
{
public:
	void Start() override 
	{
		//Core::EngineLogger::Get()->SetLevel(Log::Level::info);
		pipeline.AddStage<TestStage>(systems);
	}
	void Shutdown() override { }
};



int main()
{
	using namespace Gargantua;
	
	Gargantua::Engine e{ []() {return new Sandbox{}; }, WIDTH, HEIGHT };
	e.Run();

	return 0;
}