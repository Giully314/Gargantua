/*
* gargantua/render/render_quadbatch.ixx
* 
* PURPOSE: Provide a way to group together draw calls.
* 
* CLASSES:
*	QuadData: info about the rendering of a 2d quad.
*	QuadBatch: class for handling 2d quad batch.
* 
* DESCRIPTION:
*	A batch is a set of vertices that must be rendered. Instaed of doing a draw call for a single quad (slow),
*	we precompute the vertices and store them, then do a single draw call on all the vertices.
* 
* TODO:
*	- support for multiple shapes (circle, lines).
*	- every quad has a single color. It's a waste of space to specify the same color for each of the 4 vertices.
*/

export module gargantua.render.quad_batch;

import <vector>;
import <array>;
import <utility>;
import <span>;

import gargantua.types;
import gargantua.render.vertex_buffer;
import gargantua.render.index_buffer;
import gargantua.render.vertex_array;
import gargantua.render.texture;
import gargantua.render.subtexture;

import gargantua.math.vector;
import gargantua.math.matrix;


namespace gargantua::render
{
	constexpr auto MAX_NUM_OF_TEXTURES = 32;


	// Keeps the info about the quad that it's used as primitive to draw.
	struct QuadData
	{
		// Order is clockwise from top right. 
		// The first triangle is 0, 1, 3, the second is 1, 2, 3
		std::array<math::Vec4df, 4> vertices = {
			math::Vec4df{  0.5f,  0.5f, 0.0f, 1.0f },
			math::Vec4df{  0.5f, -0.5f, 0.0f, 1.0f },
			math::Vec4df{ -0.5f, -0.5f, 0.0f, 1.0f },
			math::Vec4df{ -0.5f,  0.5f, 0.0f, 1.0f },
		};

		
		std::array<math::Vec2df, 4> texture_coords = {
			math::Vec2df{ 0.0f, 0.0f },
			math::Vec2df{ 1.0f, 0.0f },
			math::Vec2df{ 1.0f, 1.0f },
			math::Vec2df{ 0.0f, 1.0f }
		};
		

		// TODO: is this relevant? Or it is enough to just load the indices in the IBO and delete this?
		std::vector<u32> indices;

		VertexBuffer position_vbo;
		VertexBuffer color_vbo;
		VertexBuffer texture_vbo;
		VertexBuffer texture_idx_vbo;
		VertexBuffer tiling_factor_vbo;
		IndexBuffer ibo;
		VertexArray vao;
	};


	export class QuadBatch
	{
	public:
		friend class RendererSystem;

		explicit QuadBatch() : QuadBatch(10000)
		{

		}

		explicit QuadBatch(const u32 max_num_of_quads_);


		/*
		* Clear the batch.
		*/
		auto Clear() -> void
		{
			positions.clear();
			colors.clear();
			textures.clear();
			texture_idxs.clear();
			tiling_factors.clear();
			current_num_of_quads = 0;
			current_num_of_textures = 1; // white texture is kept in index 0.
		}

		/*
		* Check if the current batch is full.
		*/
		auto IsFull() const noexcept -> bool
		{
			return max_quads_per_batch == current_num_of_quads || current_num_of_textures == MAX_NUM_OF_TEXTURES;
		}

		/*
		* Add a quad to the batch.
		*/
		auto Add(const math::Mat4df& transform, const math::Vec4df& color) -> void;
		

		/*
		* Add a quad with a texture to the batch.
		* Precondition: current number of textures < MAX_NUMBER_OF_TEXTURES (32).
		*/
		auto Add(const math::Mat4df& transform, const shared_res<Texture>& texture,
					f32 tiling_factor) -> void;


		/*
		* Add a quad with a texture to the batch and a color.
		* Precondition: current number of textures < MAX_NUMBER_OF_TEXTURES (32).
		*/
		auto Add(const math::Mat4df& transform, const math::Vec4df& color, 
			const shared_res<Texture>& texture, f32 tiling_factor) -> void;


		/*
		* Add a quad with a subtexture to the batch.
		* Precondition: current number of textures < MAX_NUMBER_OF_TEXTURES (32).
		*/
		auto Add(const math::Mat4df& transform, const SubTexture& subtexture, f32 tiling_factor) -> void;


		/*
		* Setup the vbo, ibo e textures to be drawn.
		*/
		auto SetupDraw() -> void
		{
			const std::span data_position{ positions };
			data.position_vbo.LoadSubData(data_position);

			const std::span data_color{ colors };
			data.color_vbo.LoadSubData(data_color);

			const std::span data_texture{ textures };
			data.texture_vbo.LoadSubData(data_texture);

			const std::span data_texture_idx{ texture_idxs };
			data.texture_idx_vbo.LoadSubData(data_texture_idx);

			const std::span data_tiling_factor{ tiling_factors };
			data.tiling_factor_vbo.LoadSubData(data_tiling_factor);

			for (u16 i = 0; i < current_num_of_textures; ++i)
			{
				texture_slots[i]->Bind(i);
			}
		}


	private:
		auto SetupVertexArray() -> void;

	private:
		u32 max_quads_per_batch;
		u32 max_num_of_vertices;
		u32 max_indices;
		u32 current_num_of_quads;
		QuadData data;

		std::vector<math::Vec4df> positions;
		std::vector<math::Vec4df> colors;
		std::vector<math::Vec2df> textures;
		std::vector<u32> texture_idxs;
		std::vector<f32> tiling_factors;

		u32 white_color = 0xffffffff;
		std::array<shared_res<Texture>, MAX_NUM_OF_TEXTURES> texture_slots;
		u16 current_num_of_textures;
	};

} // namespace gargantua::render2d
