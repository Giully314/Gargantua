/*
* gargantua/render/render_renderersystem.cpp
* 
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.render.renderer_system;

import <numeric>;

import gargantua.log;
import gargantua.render.renderer_command;
import gargantua.render.shader_system;

import gargantua.math.functions;
import gargantua.event;
import gargantua.glfw;


namespace gargantua::render
{
	auto RendererSystem::Startup(const u32 width, const u32 height) -> void
	{
		GRG_CORE_DEBUG("RendererSystem startup with width {} and height {}.", width, height);

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

		//non_owned_res<Shader> light_source_shader = nullptr;
		//non_owned_res<Shader> lighting_shader = nullptr;
		//if (auto s = shader_sys.Load("assets/shaders/lighting_shader.frag"); s)
		//{
		//	lighting_shader = *s;
		//}

		//if (auto s = shader_sys.Load("assets/shaders/light_source_shader.frag"); s)
		//{
		//	light_source_shader = *s;
		//}


		//// Setup light data program
		//light_data.program.LinkShaders(*vert_shader, *light_source_shader);
		

		fb_data.program.LinkShaders(*fb_vert_shader, *fb_frag_shader);
		fb_data.program.SetUniform1i("screen_texture", 0);

		fb_data.screen_fb.Initialize(width, height);
		RendererCommand::SetViewport(0, 0, width, height);

		// Setup Quad2dData
		/*Shader vert_shader{ "assets/shaders/quad_shader.vert", ShaderType::Vertex };
		Shader frag_shader{ "assets/shaders/quad_shader.frag", ShaderType::Fragment };*/
		data.program.LinkShaders(*vert_shader, *frag_shader);

		data.program.Bind();
		std::array<int, 16> textures;
		std::iota(textures.begin(), textures.end(), 0);
		data.program.SetUniformArrayInt("u_textures", textures);

		// Register events
		auto& event_dispatcher = event::EngineEventDispatcher();
		
		// TODO: THIS IS WRONG, now we are using imgui panels, so resize must be done in terms of that.
		event_dispatcher.RegisterListener<glfw::WindowResizeEvent>(
			[this](const event::BaseEvent& e)
			{
				const auto& we = static_cast<const glfw::WindowResizeEvent&>(e);
				Resize(we.new_width, we.new_height);
			});

		RendererCommand::EnableBlending();
	}

	auto RendererSystem::Shutdown() -> void
	{

	}


	auto RendererSystem::BeginScene(const math::Mat4df& camera) -> void
	{
		this->camera = camera;
		data.batch_system.Clear();
		fb_data.screen_fb.Bind();
	}

	auto RendererSystem::BeginScene(const math::Mat4df& transform, const math::Mat4df& projection) -> void
	{
		BeginScene(projection * transform.Inverse());
	}


	auto RendererSystem::EndScene() -> void
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
		fb_data.screen_fb.ColorBuffer().Bind();
		RendererCommand::DrawArray(fb_data.vao, 6);
	}

	
	auto RendererSystem::Resize(const u32 width, const u32 height) -> void
	{
		fb_data.screen_fb.Resize(width, height);
		RendererCommand::SetViewport(0, 0, width, height);
	}



	auto RendererSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const math::Vec4df& color) -> void
	{
		DrawQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, color);
	}

	

	void RendererSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const shared_res<Texture>& texture, const f32 tiling_factor)
	{
		DrawQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, texture, tiling_factor);
	}

	auto RendererSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const SubTexture& subtexture, const f32 tiling_factor) -> void
	{
		DrawQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, subtexture, tiling_factor);
	}


	auto RendererSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, const f32 rotation,
		const math::Vec4df& color) -> void
	{
		DrawRotatedQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, rotation, color);
	}


	auto RendererSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, f32 rotation,
		const shared_res<render::Texture>& texture, const f32 tiling_factor) -> void
	{
		DrawRotatedQuad(math::Vec3df{ position, 0.0f }, math::Vec3df{ size, 0.0f }, rotation, texture, tiling_factor);
	}



	auto RendererSystem::DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
		const math::Vec4df& color) -> void
	{
		auto transform = math::Transform3d::Translate(position) *
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, color);
	}



	void RendererSystem::DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
		const shared_res<Texture>& texture, const f32 tiling_factor)
	{
		auto transform = math::Transform3d::Translate(position) *
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, texture, tiling_factor);
	}


	auto RendererSystem::DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
		const SubTexture& subtexture, const f32 tiling_factor) -> void
	{
		auto transform = math::Transform3d::Translate(position)*
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, subtexture, tiling_factor);
	}


	auto RendererSystem::DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
		const math::Vec4df& color) -> void
	{
		auto transform = math::Transform3d::Translate(position) *
			math::Transform3d::RotateZ(rotation) *
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, color);
	}


	auto RendererSystem::DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
		const shared_res<render::Texture>& texture, const f32 tiling_factor) -> void
	{
		auto transform = math::Transform3d::Translate(position)*
			math::Transform3d::RotateZ(rotation)*
			math::Transform3d::Scale(size);

		data.batch_system.Add(transform, texture, tiling_factor);
	}


	auto RendererSystem::DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
		const math::Vec4df& color,
		const shared_res<Texture>& texture, const f32 tiling_factor) -> void
	{
		auto transform = math::Transform3d::Translate(position) *
			math::Transform3d::RotateZ(rotation) *
			math::Transform3d::Scale(size);
		data.batch_system.Add(transform, color, texture, tiling_factor);
	}
} // namespace gargantua::render
