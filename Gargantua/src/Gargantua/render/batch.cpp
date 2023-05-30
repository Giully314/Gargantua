/*
* gargantua/render/batch.cpp
* 
*/
module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.render.batch;

import gargantua.log.logger_system;

namespace gargantua::render
{
	QuadBatch::QuadBatch() : QuadBatch(10000)
	{

	}


	QuadBatch::QuadBatch(u32 max_num_of_quads) : max_quads_per_batch(max_num_of_quads),
		max_num_of_vertices(max_num_of_quads * 4), max_indices(max_num_of_quads * 6), current_num_of_quads(0),
		current_num_of_textures(0)
	{
		SetupVertexArray();

		// Load white texture
		shared_res<Texture2d> texture = CreateSharedRes<Texture2d>();
		texture->Fill(1, 1, &white_color);
		texture_slots[0] = std::move(texture);
		++current_num_of_textures;
	}


	auto QuadBatch::Add(const math::Mat4df& transform, const math::Vec4df& color) -> void
	{
		const f32 tiling_factor = 1.0f;
		const u32 texture_idx = 0; // White texture

		for (u32 i = 0; i < data.vertices.size(); ++i)
		{
			auto v = transform * data.vertices[i];
			positions.push_back(std::move(v));
			colors.push_back(color);
			textures.push_back(data.texture_coords[i]);
			texture_idxs.push_back(texture_idx);
			tiling_factors.push_back(tiling_factor);
		}
		++current_num_of_quads;
	}


	auto QuadBatch::Add(const math::Mat4df& transform,  
		const shared_res<Texture2d>& texture, f32 tiling_factor) -> void
	{
		// Check if the texture is already present.
		u32 texture_idx = 0;
		// start from 1 because 0 is the white texture.
		for (u32 i = 1; i < current_num_of_textures; ++i)
		{
			if (*texture == *texture_slots[i])
			{
				texture_idx = i;
				break;
			}
		}
		
		
		if (texture_idx == 0)
		{
			texture_idx = current_num_of_textures;
			texture_slots[texture_idx] = texture;
			++current_num_of_textures;
		}

		const math::Vec4df white{ 1.0f, 1.0f, 1.0f, 1.0f };
		for (u32 i = 0; i < data.vertices.size(); ++i)
		{
			auto v = transform * data.vertices[i];
			positions.push_back(std::move(v));
			colors.push_back(white);
			textures.push_back(data.texture_coords[i]);
			texture_idxs.push_back(texture_idx);
			tiling_factors.push_back(tiling_factor);
		}
		++current_num_of_quads;
	}


	auto QuadBatch::Add(const math::Mat4df& transform, const SubTexture2d& subtexture,
		f32 tiling_factor) -> void
	{
		// Check if the texture is already present.
		u32 texture_idx = 0;
		const auto& texture = subtexture.GetTexture();

		// start from 1 because 0 is the white texture.
		for (u32 i = 1; i < current_num_of_textures; ++i)
		{
			if (*texture == *texture_slots[i])
			{
				texture_idx = i;
				break;
			}
		}


		if (texture_idx == 0)
		{
			texture_idx = current_num_of_textures;
			texture_slots[texture_idx] = texture;
			++current_num_of_textures;
		}

		const math::Vec4df white{ 1.0f, 1.0f, 1.0f, 1.0f };
		const auto texture_coords = subtexture.GetCoords();
		for (u32 i = 0; i < data.vertices.size(); ++i)
		{
			auto v = transform * data.vertices[i];
			positions.push_back(std::move(v));
			colors.push_back(white);
			textures.push_back(texture_coords[i]);
			texture_idxs.push_back(texture_idx);
			tiling_factors.push_back(tiling_factor);
		}
		++current_num_of_quads;
	}


	// ********************************** PRIVATE ********************************

	auto QuadBatch::SetupVertexArray() -> void
	{

		data.position_vbo.SetLayout(VertexLayout{ 4, sizeof(f32) });
		data.position_vbo.Empty(max_num_of_vertices);

		data.color_vbo.SetLayout(VertexLayout{ 4, sizeof(f32) });
		data.color_vbo.Empty(max_num_of_vertices);

		data.texture_vbo.SetLayout(VertexLayout{ 2, sizeof(f32) });
		data.texture_vbo.Empty(max_num_of_vertices);

		data.texture_idx_vbo.SetLayout(VertexLayout{ 1, sizeof(u32) });
		data.texture_idx_vbo.Empty(max_num_of_vertices);

		data.tiling_factor_vbo.SetLayout(VertexLayout{ 1, sizeof(f32) });
		data.tiling_factor_vbo.Empty(max_num_of_vertices);

		data.vao.AddBuffer(data.position_vbo, 0);
		data.vao.AddBuffer(data.color_vbo, 1);
		data.vao.AddBuffer(data.texture_vbo, 2);
		data.vao.AddBuffer(data.texture_idx_vbo, 3);
		data.vao.AddBuffer(data.tiling_factor_vbo, 4);
		

		positions.reserve(max_num_of_vertices);
		colors.reserve(max_num_of_vertices);
		textures.reserve(max_num_of_vertices);
		texture_idxs.reserve(max_num_of_vertices);
		tiling_factors.reserve(max_num_of_vertices);

		data.indices.resize(max_quads_per_batch * 6);

		for (u32 i = 0, offset = 0; i < data.indices.size(); i += 6, offset += 4)
		{
			data.indices[i + 0] = offset + 0;
			data.indices[i + 1] = offset + 1;
			data.indices[i + 2] = offset + 3;
			data.indices[i + 3] = offset + 1;
			data.indices[i + 4] = offset + 2;
			data.indices[i + 5] = offset + 3;
		}

		//std::span t{ data.indices.data(), data.indices.size() };
		std::span t{ data.indices };
		data.ibo.Load(t);
		data.vao.AddBuffer(data.ibo);
	}

} // namespace gargantua::render