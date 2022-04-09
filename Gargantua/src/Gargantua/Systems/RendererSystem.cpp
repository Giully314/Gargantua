/*
Gargantua/Systems/RendererSystem.cpp

*/
#include "RendererSystem.hpp"

#include <glad/glad.h>

#include "Gargantua/Renderer/RendererCommand.hpp"

#include "Gargantua/Core/EngineLogger.hpp"

#include "Gargantua/Math/Vec4d.hpp"

#include "Gargantua/Event/WindowEvents.hpp"

namespace Gargantua
{
	namespace Systems
	{
		RendererSystem::RendererSystem(natural_t width, natural_t height) : camera(nullptr)
		{
			Renderer::RendererCommand::SetClearColor(Math::Vec4df{ 0.0f, 0.0f, 0.0f, 1.0f });
			Renderer::RendererCommand::EnableBlending();
			Renderer::RendererCommand::SetViewport(0, 0, width, height);
		}

		void RendererSystem::ListenToEvents(NonOwnedRes<Event::EventListenerSystem> event_list_sys)
		{
			event_list_sys->RegisterListener<Event::WindowResizeEvent>([](const Event::BaseEvent& e)
				{
					const auto& wre = static_cast<const Event::WindowResizeEvent&>(e);
					Renderer::RendererCommand::SetViewport(0, 0, wre.new_width, wre.new_height);
				});
		}

		void RendererSystem::BeginScene(NonOwnedRes<Renderer::OrthoCamera> camera)
		{
			this->camera = camera;
			Renderer::RendererCommand::Clear();
		}


		void RendererSystem::EndScene()
		{

		}


		void RendererSystem::RenderFrame()
		{
		
		}

		void RendererSystem::SetClearColor(const Math::Vec4df& color)
		{
			glClearColor(color[0], color[1], color[2], color[3]);
		}


		void RendererSystem::Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
										NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t) const
		{
			va->Bind();

			p->Bind();
			p->SetUniformMatrix4f("u_proj_view", camera->GetProjectionView());

			Renderer::RendererCommand::Draw(*eb, t);
		}

		void RendererSystem::Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
			NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t, const Math::Mat4df& transform) const
		{
			va->Bind();

			p->Bind();
			p->SetUniformMatrix4f("u_proj_view", camera->GetProjectionView());
			p->SetUniformMatrix4f("u_transform", transform);

			Renderer::RendererCommand::Draw(*eb, t);
		}


		void RendererSystem::Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
			NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t,
			NonOwnedRes<Renderer::Texture2d> texture) const
		{
			va->Bind();

			texture->Bind();

			p->Bind();
			p->SetUniformMatrix4f("u_proj_view", camera->GetProjectionView());

			Renderer::RendererCommand::Draw(*eb, t);
		}

		void RendererSystem::Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
			NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t,
			NonOwnedRes<Renderer::Texture2d> texture, const Math::Mat4df& transform) const
		{
			va->Bind();

			texture->Bind();

			p->Bind();
			p->SetUniformMatrix4f("u_proj_view", camera->GetProjectionView());
			p->SetUniformMatrix4f("u_transform", transform);

			Renderer::RendererCommand::Draw(*eb, t);
		}
	} //namespace Systems
} //namespace Gargantua