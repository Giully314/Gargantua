/*
* gargantua/render/renderer2d_system.cpp
* 
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.render.renderer2d_system;

import <numeric>;

import gargantua.render.renderer_command;
import gargantua.render.shader_system;

import gargantua.math.math_functions;

import gargantua.platform;

namespace gargantua::render
{
	auto Renderer2dSystem::Startup() -> void
	{
		// Setup FrameBufferData
		constexpr f32 screen_vertices[12] = 
		{ 
			-1.0f,  1.0f, 
			-1.0f, -1.0f, 
			 1.0f, -1.0f, 

			-1.0f,  1.0f, 
			 1.0f, -1.0f, 
			 1.0f,  1.0f, 
		};

		constexpr f32 texture_vertices[12] =
		{
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 0.0f,
			1.0f, 1.0f
		};
		std::span s{ screen_vertices, 12 };
		std::span t{ texture_vertices, 12 };
		fb_data.screen_vbo.Load(s, 2);
		fb_data.texture_vbo.Load(t, 2);
		fb_data.vao.AddBuffer(fb_data.screen_vbo, 0);
		fb_data.vao.AddBuffer(fb_data.texture_vbo, 1);

		// Shader fb_vert_shader{ "assets/shaders/fb_shader.vert", ShaderType::Vertex };
		// Shader fb_frag_shader{ "assets/shaders/fb_shader.frag", ShaderType::Fragment };
		
		// TODO: the name of the shaders shouldn't be hardcoded in this way.
		// TODO: if the shader aren't loaded, signal errors.
		auto& shader_sys = ShaderSystem::Instance();
		
		non_owned_res<Shader> fb_vert_shader = nullptr;
		non_owned_res<Shader> fb_frag_shader = nullptr;
		if (auto s = shader_sys.Load("assets/shaders/fb_shader.vert"); s)
		{
			fb_vert_shader = *s;
		}
		
		if (auto s = shader_sys.Load("assets/shaders/fb_shader.frag"); s)
		{
			fb_frag_shader = *s;
		}
		
		non_owned_res<Shader> vert_shader = nullptr;
		non_owned_res<Shader> frag_shader = nullptr;
		if (auto s = shader_sys.Load("assets/shaders/quad_shader.vert"); s)
		{
			vert_shader = *s;
		}

		if (auto s = shader_sys.Load("assets/shaders/quad_shader.frag"); s)
		{
			frag_shader = *s;
		}

		non_owned_res<Shader> light_source_shader = nullptr;
		non_owned_res<Shader> lighting_shader = nullptr;
		if (auto s = shader_sys.Load("assets/shaders/lighting_shader.frag"); s)
		{
			lighting_shader = *s;
		}

		if (auto s = shader_sys.Load("assets/shaders/light_source_shader.frag"); s)
		{
			light_source_shader = *s;
		}


		// Setup light data program
		light_data.program.LinkShaders(*vert_shader, *light_source_shader);
		

		fb_data.program.LinkShaders(*fb_vert_shader, *fb_frag_shader);
		fb_data.program.SetUniform1i("screen_texture", 0);

		const auto& props = platform::PlatformSystem::Instance().GetWindowProperties();
		fb_data.screen_fb.Initialize(props.width, props.height);
		RendererCommand::SetViewport(0, 0, props.width, props.height);

		// Setup Quad2dData
		/*Shader vert_shader{ "assets/shaders/quad_shader.vert", ShaderType::Vertex };
		Shader frag_shader{ "assets/shaders/quad_shader.frag", ShaderType::Fragment };*/
		data.program.LinkShaders(*vert_shader, *frag_shader);

		data.program.Bind();
		std::array<int, 16> textures;
		std::iota(textures.begin(), textures.end(), 0);
		data.program.SetUniformArrayInt("u_textures", textures);

		// Register events
		auto& event_dispatcher = platform::PlatformEventDispatcher::Instance();
		
		// TODO: THIS IS WRONG, now we are using imgui panels, so resize must be done in terms of that.
		event_dispatcher.RegisterListener<platform::WindowResizeEvent>(
			[this](const platform::WindowResizeEvent& event)
			{
				Resize(event.new_width, event.new_height);
			});

		RendererCommand::EnableBlending();
	}

	auto Renderer2dSystem::Shutdown() -> void
	{

	}


	auto Renderer2dSystem::BeginScene(const math::Mat4df& camera) -> void
	{
		this->camera = camera;
		data.batch_system.Clear();
		fb_data.screen_fb.Bind();
	}

	auto Renderer2dSystem::BeginScene(const math::Mat4df& transform, const math::Mat4df& projection) -> void
	{
		BeginScene(projection * transform.Inverse());
	}


	auto Renderer2dSystem::EndScene() -> void
	{
		RendererCommand::Clear();
		data.program.Bind();
		data.program.SetUniformMatrix4f("u_view_proj", camera);
		for (auto& batch : data.batch_system.GetBatches())
		{
			batch.SetupDraw();
			RendererCommand::DrawIndexed(batch.data.vao, batch.current_num_of_quads * 6);
		}
		fb_data.screen_fb.Unbind();

		// Draw the frame buffer.
		fb_data.program.Bind();
		fb_data.screen_fb.GetColorBuffer().Bind();
		RendererCommand::DrawArray(fb_data.vao, 6);
	}

	
	auto Renderer2dSystem::Resize(u32 width, u32 height) -> void
	{
		fb_data.screen_fb.Resize(width, height);
		RendererCommand::SetViewport(0, 0, width, height);
	}



	auto Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const math::Vec4df& color) -> void
	{
		DrawQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, color);
	}

	

	void Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const shared_res<Texture2d>& texture, const f32 tiling_factor)
	{
		DrawQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, texture, tiling_factor);
	}

	auto Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const SubTexture2d& subtexture, const f32 tiling_factor) -> void
	{
		DrawQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, subtexture, tiling_factor);
	}


	auto Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, const f32 rotation,
		const math::Vec4df& color) -> void
	{
		DrawRotatedQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, rotation, color);
	}


	auto Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, f32 rotation,
		const shared_res<render::Texture2d>& texture, const f32 tiling_factor) -> void
	{
		DrawRotatedQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, rotation, texture, tiling_factor);
	}



	auto Renderer2dSystem::DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
		const math::Vec4df& color) -> void
	{
		auto transform = math::Transform3d::Translate(position) *
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, color);
	}



	void Renderer2dSystem::DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
		const shared_res<Texture2d>& texture, const f32 tiling_factor)
	{
		auto transform = math::Transform3d::Translate(position) *
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, texture, tiling_factor);
	}


	auto Renderer2dSystem::DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
		const SubTexture2d& subtexture, const f32 tiling_factor) -> void
	{
		auto transform = math::Transform3d::Translate(position)*
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, subtexture, tiling_factor);
	}


	auto Renderer2dSystem::DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
		const math::Vec4df& color) -> void
	{
		auto transform = math::Transform3d::Translate(position) *
			math::Transform3d::RotateZ(rotation) *
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, color);
	}


	auto Renderer2dSystem::DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
		const shared_res<render::Texture2d>& texture, const f32 tiling_factor) -> void
	{
		auto transform = math::Transform3d::Translate(position)*
			math::Transform3d::RotateZ(rotation)*
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, texture, tiling_factor);
	}


	auto Renderer2dSystem::DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
		const math::Vec4df& color,
		const shared_res<Texture2d>& texture, const f32 tiling_factor) -> void
	{
		auto transform = math::Transform3d::Translate(position) *
			math::Transform3d::RotateZ(rotation) *
			math::Transform3d::Scale(size);
		data.batch_system.Add(transform, color, texture, tiling_factor);
	}
} // namespace gargantua::render
