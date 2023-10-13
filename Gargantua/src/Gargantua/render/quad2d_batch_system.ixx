/*
* gargantua/render/quad2dbatch_system.ixx
* 
* PURPOSE: Manage batches.
* 
* CLASSES:
*	Quad2dBatchSystem: manage all the batches.
* 
* DESCRIPTION:
*	The batch system handles all the operations on a batch. If the batch is full, create a new one; setup
*	the batches for the draw. For more info about batch check quad2d_batch.ixx.
* 
* 
* TODO:
*	- creation/destruction of batches could be expansive for the create/destroy of opengl buffers; 
*		there could be an option of setting a minimum of batches to be reused instead of clearing the vector
*		at the end of each frame.
*/

export module gargantua.render.quad2d_batch_system;

import <vector>;

import gargantua.types;

import gargantua.render.texture2d;
import gargantua.render.subtexture2d;
import gargantua.render.quad2d_batch;

import gargantua.math.vec4d;
import gargantua.math.mat4d;

namespace gargantua::render
{
	export
	class Quad2dBatchSystem
	{
	public:

		Quad2dBatchSystem() : Quad2dBatchSystem(10000)
		{

		}

		Quad2dBatchSystem(u32 max_num_of_quads_) : max_num_of_quads(max_num_of_quads_)
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


		auto GetBatches() -> std::vector<Quad2dBatch>&
		{
			return quad_batches;
		}

	private:
		std::vector<Quad2dBatch> quad_batches;
		u32 max_num_of_quads;
	};
	
} // namespace gargantua::render
