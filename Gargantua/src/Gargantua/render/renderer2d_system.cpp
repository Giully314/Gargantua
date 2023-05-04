/*
* gargantua/render/renderer2d_system.cpp
* 
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.render.renderer2d_system;

import <numeric>;

import gargantua.math.math_functions;
import gargantua.render.renderer_command;


namespace gargantua::render
{
	auto Renderer2dSystem::Startup() -> void
	{
		Shader vert_shader{ "src/shaders/quad_shader.vert", ShaderType::Vertex };
		Shader frag_shader{ "src/shaders/quad_shader.frag", ShaderType::Fragment };
		data.program.LinkShaders(vert_shader, frag_shader);

		data.program.Bind();
		std::array<int, 16> textures;
		std::iota(textures.begin(), textures.end(), 0);
		data.program.SetUniformArrayInt("u_textures", textures);
	}

	auto Renderer2dSystem::Shutdown() -> void
	{

	}


	auto Renderer2dSystem::EndScene() -> void
	{
		RendererCommand::Clear();
		data.program.Bind();
		data.program.SetUniformMatrix4f("u_proj_view", camera);
		for (auto& batch : data.batch_system.GetBatches())
		{
			batch.SetupDraw();
			RendererCommand::DrawIndexed(batch.data.vao, batch.current_num_of_quads * 6);
		}
	}



	auto Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const math::Vec4df& color) -> void
	{
		auto transform = math::Transform3d::Translate(math::Vec3df{ position, 0.0f }) *
			math::Transform3d::Scale(math::Vec3df{ size, 0.0f });

		data.batch_system.Add(transform, color);
	}

	

	void Renderer2dSystem::DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
		const shared_res<Texture2d>& texture, f32 tiling_factor)
	{
		auto transform = math::Transform3d::Translate(math::Vec3df{ position, 0.0f }) *
			math::Transform3d::Scale(math::Vec3df{ size, 0.0f });
		
		data.batch_system.Add(transform, texture, tiling_factor);
	}


	auto Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, f32 rotation,
		const math::Vec4df& color) -> void
	{
		auto transform = math::Transform3d::Translate(math::Vec3df{ position, 0.0f }) *
			math::Transform3d::RotateZ(rotation) *
			math::Transform3d::Scale(math::Vec3df{ size, 0.0f });

		data.batch_system.Add(transform, color);
	}


	auto Renderer2dSystem::DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, f32 rotation,
		const shared_res<render::Texture2d>& texture, f32 tiling_factor) -> void
	{
		auto transform = math::Transform3d::Translate(math::Vec3df{ position, 0.0f }) *
			math::Transform3d::RotateZ(rotation) *
			math::Transform3d::Scale(math::Vec3df{ size, 0.0f });

		data.batch_system.Add(transform, texture, tiling_factor);
	}

} // namespace gargantua::render
