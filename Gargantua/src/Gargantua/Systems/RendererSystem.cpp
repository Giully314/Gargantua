/*
Gargantua/Systems/RendererSystem.cpp

*/
#include "RendererSystem.hpp"

#include <glad/glad.h>

#include "Gargantua/Core/EngineLogger.hpp"


namespace Gargantua
{
	namespace Systems
	{
		void RendererSystem::BeginScene(NonOwnedRes<Renderer::OrthoCamera> camera)
		{
			this->camera = camera;
		}


		void RendererSystem::EndScene()
		{

		}


		void RendererSystem::RenderFrame()
		{
			for (auto& cmd : commands)
			{
				cmd.program->Bind();
				cmd.program->SetUniformMatrix4f("u_proj_view", camera->GetProjectionView());
				cmd.va->Bind();
				glDrawElements((GLenum)(cmd.topology), cmd.eb->GetCount(), cmd.eb->GetGLType(), nullptr);
			}
			commands.clear();
		}

		void RendererSystem::SetClearColor(const Math::Vec4df& color)
		{
			glClearColor(color[0], color[1], color[2], color[3]);
		}


		void RendererSystem::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		void RendererSystem::Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
										NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t)
		{
			commands.emplace_back(va, eb, p, t);
		}
	} //namespace Systems
} //namespace Gargantua