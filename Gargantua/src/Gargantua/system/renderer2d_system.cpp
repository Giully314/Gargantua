/*
gargantua/system/renderer2d_system.cpp
*/

module gargantua.system.renderer2d_system;

import gargantua.render.vertex_buffer;
import gargantua.render.render_utlity;

import gargantua.event.window_events;

import gargantua.math.math_functions;




namespace gargantua::system
{

	Renderer2dSystem::Renderer2dSystem(natural_t width, natural_t height)
	{
		data.fb = render::Utility::CreateFB(width, height);
		data.fb->Bind();

		render::RendererCommand::SetClearColor(math::Vec4df{ 0.0f, 0.0f, 0.0f, 1.0f });
		render::RendererCommand::EnableBlending();

		data.fb->Unbind();

		render::RendererCommand::SetViewport(0, 0, width, height);


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


		SharedRes<render::VertexBuffer> center_square = render::Utility::CreateVB(vertices, 8, 2,
			render::DrawMode::static_draw);

		SharedRes<render::VertexBuffer> square_text = render::Utility::CreateVB(text_coords, 8, 2,
			render::DrawMode::static_draw);

		data.eb = render::Utility::CreateEB(elements, 6, render::DrawMode::static_draw);
		data.va_quad = render::Utility::CreateVA();

		natural_t white_color = 0xffffffff;

		data.tx_white = render::Utility::CreateTX2d(1, 1, &white_color);

		data.va_quad->AddVertexBuffer(*center_square, 0);
		data.va_quad->AddVertexBuffer(*square_text, 1);
		data.va_quad->AddElementBuffer(*data.eb);


		data.fb_quad = render::Utility::CreateVA();

		SharedRes<render::VertexBuffer> screen_square = render::Utility::CreateVB(fb_vertices, 8, 2,
			render::DrawMode::static_draw);

		SharedRes<render::VertexBuffer> screen_text = render::Utility::CreateVB(text_coords, 8, 2,
			render::DrawMode::static_draw);

		data.fb_eb = render::Utility::CreateEB(elements, 6, render::DrawMode::static_draw);

		data.fb_quad->AddVertexBuffer(*screen_square, 0);
		data.fb_quad->AddVertexBuffer(*screen_text, 1);
		data.fb_quad->AddElementBuffer(*data.fb_eb);
	}



	void Renderer2dSystem::BeginScene(const math::Mat4df& proj_view)
	{
		data.fb->Bind();
		data.proj_view = proj_view;
		data.program->Bind();
		data.program->SetUniformMatrix4f(data.uniforms["camera"], proj_view);
		data.program->Unbind();
		render::RendererCommand::Clear();
	}


	void Renderer2dSystem::EndScene()
	{
		data.fb->Unbind();
		data.fb_program->Bind();
		data.fb->GetColorBuffer().Bind();
		data.fb_quad->Bind();

		render::RendererCommand::Draw(*data.fb_eb);

		data.fb_program->Unbind();
	}


	void Renderer2dSystem::ListenAndRegisterEvents(SharedRes<system::EventSystem> event_sys)
	{
		//The frame buffer is not linked to the window anymore; it is linked to the imgui panel.
		event_sys->RegisterListener<event::WindowResizeEvent>([this](const event::BaseEvent& e)
			{
				const auto& wre = static_cast<const event::WindowResizeEvent&>(e);
				render::RendererCommand::SetViewport(0, 0, wre.new_width, wre.new_height);
				data.fb->Resize(wre.new_width, wre.new_height);
			});
	}


	/************************** DRAW QUAD ***************************************/

	void Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const render::Texture2d& texture)
	{
		DrawQuad(position, size, data.white, texture, 1.0f);
	}


	void Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const math::Vec4df& color)
	{
		DrawQuad(position, size, color, *data.tx_white, 1.0f);
	}


	void Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const math::Vec4df& color, const render::Texture2d& texture)
	{
		DrawQuad(position, size, color, texture, 1.0f);
	}

	void Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const render::Texture2d& texture, real_t tiling_factor)
	{
		DrawQuad(position, size, data.white, texture, 1.0f);
	}


	void Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const math::Vec4df& color, const render::Texture2d& texture, real_t tiling_factor)
	{
		auto transform = math::Transform3d::Translate(math::Vec3df{ position, 0.0f }) *
			math::Transform3d::Scale(math::Vec3df{ size, 0.0f });

		data.program->Bind();
		data.program->SetUniformMatrix4f(data.uniforms["transform"], transform);
		data.program->SetUniform4f(data.uniforms["color"], color);
		data.program->SetUniform1f(data.uniforms["tiling_factor"], tiling_factor);

		texture.Bind();
		data.va_quad->Bind();

		render::RendererCommand::Draw(*data.eb);
	}

	/************************** DRAW QUAD ***************************************/


	/************************** DRAW ROTATED QUAD ***************************************/

	void Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
		const render::Texture2d& texture)
	{
		DrawRotatedQuad(position, size, rotation, data.white, texture, 1.0f);
	}


	void Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
		const math::Vec4df& color)
	{
		DrawRotatedQuad(position, size, rotation, color, *data.tx_white, 1.0f);
	}


	void Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
		const math::Vec4df& color, const render::Texture2d& texture)
	{
		DrawRotatedQuad(position, size, rotation, color, texture, 1.0f);
	}


	void Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
		const render::Texture2d& texture, real_t tiling_factor)
	{
		DrawRotatedQuad(position, size, rotation, data.white, texture, tiling_factor);
	}




	void Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
		const math::Vec4df& color, const render::Texture2d& texture,
		real_t tiling_factor)
	{
		auto transform = math::Transform3d::Translate(math::Vec3df{ position, 0.0f }) *
			math::Transform3d::RotateZ(math::Angles::ToRad(rotation)) *
			math::Transform3d::Scale(math::Vec3df{ size, 0.0f });

		data.program->Bind();
		data.program->SetUniformMatrix4f(data.uniforms["transform"], transform);
		data.program->SetUniform4f(data.uniforms["color"], color);
		data.program->SetUniform1f(data.uniforms["tiling_factor"], tiling_factor);

		texture.Bind();
		data.va_quad->Bind();

		render::RendererCommand::Draw(*data.eb);
	}

	/************************** DRAW ROTATED QUAD ***************************************/


} //namespace gargantua::system