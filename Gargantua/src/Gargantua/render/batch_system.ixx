/*
* gargantua/render/batch_system.ixx
* 
* PURPOSE: Manage batches.
* 
* CLASSES:
*	BatchSystem: manage all the batches.
* 
* DESCRIPTION:
*	The batch system handles all the operations on a batch. If the batch is full, create a new one; setup
*	the batches for the draw.
*/

export module gargantua.render.batch_system;

import <vector>;

import gargantua.types;

import gargantua.render.batch;
import gargantua.render.texture2d;
import gargantua.render.subtexture2d;

import gargantua.math.vec4d;
import gargantua.math.mat4d;

namespace gargantua::render
{
	export
	class QuadBatchSystem
	{
	public:

		QuadBatchSystem() : QuadBatchSystem(10000)
		{

		}

		QuadBatchSystem(u32 max_num_of_quads_) : max_num_of_quads(max_num_of_quads_)
		{
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


		auto Add(const math::Mat4df& transform, const shared_res<Texture2d>& texture,
			f32 tiling_factor) -> void
		{
			if (quad_batches.back().IsFull()) [[unlikely]]
			{
				// Create a new batch.
				quad_batches.emplace_back(max_num_of_quads);
			}

			quad_batches.back().Add(transform, texture, tiling_factor);
		}


		auto Add(const math::Mat4df& transform, const math::Vec4df& color, 
			const shared_res<Texture2d>& texture, f32 tiling_factor) -> void
		{
			if (quad_batches.back().IsFull()) [[unlikely]]
			{
				// Create a new batch.
				quad_batches.emplace_back(max_num_of_quads);
			}

			quad_batches.back().Add(transform, color, texture, tiling_factor);
		}


		auto Add(const math::Mat4df& transform, const SubTexture2d& subtexture,
			f32 tiling_factor) -> void
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


		auto GetBatches() -> std::vector<QuadBatch>&
		{
			return quad_batches;
		}

	private:
		std::vector<QuadBatch> quad_batches;
		u32 max_num_of_quads;
	};
	
} // namespace gargantua::render
