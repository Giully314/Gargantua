#include <glad/glad.h>

#include "Gargantua/Engine.hpp"
#include "Gargantua/Types.hpp"


#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Core/Application.hpp"
#include "Gargantua/Core/Stage.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Renderer/VertexBuffer.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/VertexArray.hpp"
#include "Gargantua/Renderer/Shader.hpp"
#include "Gargantua/Renderer/Program.hpp"
#include "Gargantua/Renderer/Types.hpp"

#include "Gargantua/Math/Vec4d.hpp"


#include "Math/TestMat4d.hpp"


#include <imgui.h>

#include <iostream>

using namespace Gargantua;


class TestStage : public Gargantua::Core::Stage
{
public:
	TestStage() : Gargantua::Core::Stage("TestStage")
	{
		float vertices[] =
		{
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		unsigned short elements[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;
		color[3] = 1.0f;


		vb.Create();
		vb.Load(vertices, 12, 3, Renderer::BufferElementType::float_t, Renderer::DrawMode::static_draw);

		eb.Create();
		eb.Load(elements, 6, Renderer::BufferElementType::unsigned_short_t, Renderer::DrawMode::static_draw);

		va.Create();

		va.AddElementBuffer(eb);

		va.AddVertexBuffer(vb, 0);


		vert_shad.Create(Renderer::ShaderType::vertex_shader);
		frag_shad.Create(Renderer::ShaderType::fragment_shader);
						
		vert_shad.Compile("C:\\Users\\Giully\\source\\repos\\Gargantua\\Gargantua\\src\\Gargantua\\Renderer\\Shaders\\Test.vert");
		frag_shad.Compile("C:\\Users\\Giully\\source\\repos\\Gargantua\\Gargantua\\src\\Gargantua\\Renderer\\Shaders\\CustomColor.frag");

		program.Create();
		program.Link(&vert_shad, &frag_shad);


	}

	~TestStage()
	{
		vb.Destroy();
		eb.Destroy();
		va.Destroy();
		vert_shad.Destroy();
		frag_shad.Destroy();
		program.Destroy();
	}


	void Start() override
	{
		va.Bind();
		program.Bind();
		program.SetUniformFloat4("my_color", color);
	}

	void End() override
	{
		va.Unbind();
		program.Unbind();
	}

	void Execute(const Gargantua::Time::TimeStep& ts) override 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, eb.GetCount(), (GLenum)eb.GetInfo().type, nullptr);
	}


	void RenderGUI() override
	{
		//ImGui::Text("CIAO COME STAI");
		ImGui::Begin("Color setting");

		ImGui::ColorEdit4("Color", &color[0]);
		
		ImGui::End();
	}

private:
	Renderer::VertexBuffer vb;
	Renderer::ElementBuffer eb;
	Renderer::VertexArray va;
	Renderer::Shader vert_shad;
	Renderer::Shader frag_shad;
	Renderer::Program program;
	Math::Vec4df color;
};



class Sandbox : public Gargantua::Core::Application
{
public:
	void Start() override 
	{
		Core::EngineLogger::Get()->SetLevel(Log::Level::info);
		pipeline.AddStage<TestStage>();
	}
	void Shutdown() override { }
};



int main()
{
	using namespace Gargantua;
	
	/*Gargantua::Engine e{ []() {return new Sandbox{}; } };
	e.Run();*/

	Test::TestMat4d test;
	test.RunTest();

	return 0;
}