/*
Gargantua/Systems/Renderer2dSystem.cpp
*/
#include "Renderer2dSystem.hpp"

#include "Gargantua/Renderer/VertexBuffer.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/Utility.hpp"


#include "Gargantua/Event/WindowEvents.hpp"


#include "Gargantua/Math/MathFunctions.hpp"


namespace Gargantua
{
	namespace Systems
	{
		Renderer2dSystem::Renderer2dSystem(natural_t width, natural_t height)
		{
			data.fb = Renderer::Utility::CreateFB(width, height);
			data.fb->Bind();

			Renderer::RendererCommand::SetClearColor(Math::Vec4df{ 0.0f, 0.0f, 0.0f, 1.0f });
			Renderer::RendererCommand::EnableBlending();

			data.fb->Unbind();

			Renderer::RendererCommand::SetViewport(0, 0, width, height);


			real_t fb_vertices[] =
			{
				-1.0f,   1.0f, //top left
				-1.0f,  -1.0f, //bottom left
				 1.0f,  -1.0f,//bottom right
				 1.0f,   1.0f,//top right
			};

			real_t vertices[] =
			{
				-0.5f,   0.5f, //top left
				-0.5f,  -0.5f, //bottom left
				 0.5f,  -0.5f,//bottom right
				 0.5f,   0.5f,//top right
			};

			real_t text_coords[] =
			{
				0.0f, 1.0f,    // top left 
				0.0f, 0.0f,   // bottom left
				1.0f, 0.0f,   // bottom right
				1.0f, 1.0f,   // top right
			};

			natural16_t elements[] =
			{
				0, 1, 2,
				0, 3, 2
			};


			data.uniforms["camera"] = "u_proj_view";
			data.uniforms["transform"] = "u_transform";
			data.uniforms["color"] = "u_color";
			data.uniforms["tiling_factor"] = "u_tiling_factor";


			SharedRes<Renderer::VertexBuffer> center_square = Renderer::Utility::CreateVB(vertices, 8, 2,
				Renderer::DrawMode::static_draw);

			SharedRes<Renderer::VertexBuffer> square_text = Renderer::Utility::CreateVB(text_coords, 8, 2,
				Renderer::DrawMode::static_draw);

			data.eb = Renderer::Utility::CreateEB(elements, 6, Renderer::DrawMode::static_draw);
			data.va_quad = Renderer::Utility::CreateVA();

			natural_t white_color = 0xffffffff;
			
			data.tx_white = Renderer::Utility::CreateTX2d(1, 1, &white_color);

			data.va_quad->AddVertexBuffer(*center_square, 0);
			data.va_quad->AddVertexBuffer(*square_text, 1);
			data.va_quad->AddElementBuffer(*data.eb);


			data.fb_quad = Renderer::Utility::CreateVA();

			SharedRes<Renderer::VertexBuffer> screen_square = Renderer::Utility::CreateVB(fb_vertices, 8, 2,
				Renderer::DrawMode::static_draw);

			SharedRes<Renderer::VertexBuffer> screen_text = Renderer::Utility::CreateVB(text_coords, 8, 2,
				Renderer::DrawMode::static_draw);
			
			data.fb_eb = Renderer::Utility::CreateEB(elements, 6, Renderer::DrawMode::static_draw);

			data.fb_quad->AddVertexBuffer(*screen_square, 0);
			data.fb_quad->AddVertexBuffer(*screen_text, 1);
			data.fb_quad->AddElementBuffer(*data.fb_eb);
		}


		void Renderer2dSystem::BeginScene(const Renderer::OrthoCamera& camera)
		{
			data.fb->Bind();
			data.proj_view = camera.GetProjectionView();
			data.program->Bind();
			data.program->SetUniformMatrix4f(data.uniforms["camera"], data.proj_view);
			data.program->Unbind();
			Renderer::RendererCommand::Clear();
		}
		

		void Renderer2dSystem::BeginScene(const Math::Mat4df& proj_view)
		{
			data.fb->Bind();
			data.proj_view = proj_view;
			data.program->Bind();
			data.program->SetUniformMatrix4f(data.uniforms["camera"], proj_view);
			data.program->Unbind();
			Renderer::RendererCommand::Clear();
		}


		void Renderer2dSystem::EndScene()
		{
			data.fb->Unbind();
			data.fb_program->Bind();
			data.fb->GetColorBuffer().Bind();
			data.fb_quad->Bind();

			Renderer::RendererCommand::Draw(*data.fb_eb);

			data.fb_program->Unbind();
		}


		void Renderer2dSystem::ListenAndRegisterEvents(SharedRes<Systems::EventSystem> event_sys)
		{
			//The frame buffer is not linked to the window anymore; it is linked to the imgui panel.
			event_sys->RegisterListener<Event::WindowResizeEvent>([this](const Event::BaseEvent& e)
				{
					const auto& wre = static_cast<const Event::WindowResizeEvent&>(e);
					Renderer::RendererCommand::SetViewport(0, 0, wre.new_width, wre.new_height);
					data.fb->Resize(wre.new_width, wre.new_height);
				});
		}


		/************************** DRAW QUAD ***************************************/

		void Renderer2dSystem::DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
			const Renderer::Texture2d& texture)
		{
			DrawQuad(position, size, data.white, texture, 1.0f);
		}


		void Renderer2dSystem::DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
			const Math::Vec4df& color)
		{
			DrawQuad(position, size, color, *data.tx_white, 1.0f);
		}


		void Renderer2dSystem::DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
			const Math::Vec4df& color, const Renderer::Texture2d& texture)
		{
			DrawQuad(position, size, color, texture, 1.0f);
		}

		void Renderer2dSystem::DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
			const Renderer::Texture2d& texture, real_t tiling_factor)
		{
			DrawQuad(position, size, data.white, texture, 1.0f);
		}


		void Renderer2dSystem::DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
			const Math::Vec4df& color, const Renderer::Texture2d& texture, real_t tiling_factor)
		{
			auto transform = Math::Transform3d::Translate(Math::Vec3df{ position, 0.0f }) *
				Math::Transform3d::Scale(Math::Vec3df{ size, 0.0f });

			data.program->Bind();
			data.program->SetUniformMatrix4f(data.uniforms["transform"], transform);
			data.program->SetUniform4f(data.uniforms["color"], color);
			data.program->SetUniform1f(data.uniforms["tiling_factor"], tiling_factor);

			texture.Bind();
			data.va_quad->Bind();

			Renderer::RendererCommand::Draw(*data.eb);
		}

		/************************** DRAW QUAD ***************************************/
		
		
		/************************** DRAW ROTATED QUAD ***************************************/

		void Renderer2dSystem::DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
			const Renderer::Texture2d& texture)
		{
			DrawRotatedQuad(position, size, rotation, data.white, texture, 1.0f);
		}


		void Renderer2dSystem::DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
			const Math::Vec4df& color)
		{
			DrawRotatedQuad(position, size, rotation, color, *data.tx_white, 1.0f);
		}


		void Renderer2dSystem::DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
			const Math::Vec4df& color, const Renderer::Texture2d& texture)
		{
			DrawRotatedQuad(position, size, rotation, color, texture, 1.0f);
		}


		void Renderer2dSystem::DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
			const Renderer::Texture2d& texture, real_t tiling_factor)
		{
			DrawRotatedQuad(position, size, rotation, data.white, texture, tiling_factor);
		}



		
		void Renderer2dSystem::DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
			const Math::Vec4df& color, const Renderer::Texture2d& texture,
			real_t tiling_factor)
		{
			auto transform = Math::Transform3d::Translate(Math::Vec3df{ position, 0.0f }) *
				Math::Transform3d::RotateZ(Math::Angles::ToRad(rotation)) * 
				Math::Transform3d::Scale(Math::Vec3df{ size, 0.0f });

			data.program->Bind();
			data.program->SetUniformMatrix4f(data.uniforms["transform"], transform);
			data.program->SetUniform4f(data.uniforms["color"], color);
			data.program->SetUniform1f(data.uniforms["tiling_factor"], tiling_factor);

			texture.Bind();
			data.va_quad->Bind();

			Renderer::RendererCommand::Draw(*data.eb);
		}
		
		/************************** DRAW ROTATED QUAD ***************************************/



	} //namespace Systems
} //namespace Gargantua