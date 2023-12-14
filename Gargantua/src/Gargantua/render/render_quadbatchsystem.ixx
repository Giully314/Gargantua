/*
* gargantua/render/render_quadbatchsystem.ixx
* 
* PURPOSE: Provide automatic batch management.
* 
* CLASSES:
*	QuadBatchSystem: class for automatic batch management (allocation of new batches, draw).
* 
* DESCRIPTION:
*	The batch system handles all the operations on a batch. If the batch is full, create a new one; setup
*	the batches for the draw. For more info about batch check render_quad2dbatch.ixx.
* 
* 
* TODO:
*	- creation/destruction of batches could be expansive for the create/destroy of opengl buffers; 
*		there could be an option of setting a minimum of batches to be reused instead of clearing the vector
*		at the end of each frame.
*/

module;

#include <gargantua/log/logger_macro.hpp>

export module gargantua.render.quad_batch_system;

import <vector>;

import gargantua.types;
import gargantua.log;

import gargantua.render.texture;
import gargantua.render.subtexture;
import gargantua.render.quad_batch;

import gargantua.math.vec4d;
import gargantua.math.mat4d;

namespace gargantua::render
{
	export class QuadBatchSystem
	{
	public:

		QuadBatchSystem() : QuadBatchSystem(10000)
		{

		}

		QuadBatchSystem(const u32 max_num_of_quads_) : max_num_of_quads(max_num_of_quads_)
		{
			GRG_CORE_DEBUG("QuadBatchSystem startup with {} max num of quads.", max_num_of_quads);
			quad_batches.emplace_back(max_num_of_quads);
		}


		auto Add(const math::Mat4df& transform, const math::Vec4df& color) -> void
		{
			if (quad_batches.back().IsFull()) [[unlikely]]
			{
				// Create a new batch.
				quad_batches.emplace_back(max_num_of_quads);
			}

			quad_batches.back().Add(transform, color);
		}


		auto Add(const math::Mat4df& transform, const shared_res<Texture>& texture,
			const f32 tiling_factor) -> void
		{
			if (quad_batches.back().IsFull()) [[unlikely]]
			{
				// Create a new batch.
				quad_batches.emplace_back(max_num_of_quads);
			}

			quad_batches.back().Add(transform, texture, tiling_factor);
		}


		auto Add(const math::Mat4df& transform, const math::Vec4df& color, 
			const shared_res<Texture>& texture, const f32 tiling_factor) -> void
		{
			if (quad_batches.back().IsFull()) [[unlikely]]
			{
				// Create a new batch.
				quad_batches.emplace_back(max_num_of_quads);
			}

			quad_batches.back().Add(transform, color, texture, tiling_factor);
		}


		auto Add(const math::Mat4df& transform, const SubTexture& subtexture,
			const f32 tiling_factor) -> void
		{
			if (quad_batches.back().IsFull()) [[unlikely]]
			{
				// Create a new batch.
				quad_batches.emplace_back(max_num_of_quads);
			}

			quad_batches.back().Add(transform, subtexture, tiling_factor);
		}

		// Load the data into the vertex buffers.
		/*auto SetupDraw() -> void
		{
			for (auto& batch : quad_batches)
			{
				batch.SetupDraw();
			}
		}*/

		// Delete all the batches except the first one.
		// This should be called at the start/end of every scene.
		auto Clear() -> void
		{			
			quad_batches.resize(1);
			quad_batches.back().Clear();
		}


		// TODO: return a view instaed of the vector.
		auto GetBatches() -> std::vector<QuadBatch>&
		{
			return quad_batches;
		}

	private:
		std::vector<QuadBatch> quad_batches;
		u32 max_num_of_quads;
	};
	
} // namespace gargantua::render
