/*
* gargantua/render/render_indexbuffer.ixx
* 
* PURPOSE: Provide RAII implementation for opengl element buffer.
*	
* CLASSES:
*	IndexBuffer: class for opengl element buffer.
* 
* DESCRIPTION:
*	This component provides implementation of a wrapper for opengl element buffer. 
*	It stores the information about the indexes of the vertices to be used during draw.
*/

export module gargantua.render.index_buffer;

import <span>;

import gargantua.types;
import gargantua.render.base_buffer;
import gargantua.render.render_info;

namespace gargantua::render
{
	export class IndexBuffer : public BaseBuffer
	{
	public:
		auto Load(const std::span<u32> data, const BufferDraw draw = BufferDraw::Static) -> void
		{
			BaseBuffer::Load(static_cast<void*>(data.data()), data.size_bytes(), draw);
			index_count = data.size();
		}

		auto Count() const noexcept -> u32
		{
			return index_count;
		}

	private:
		u32 index_count = 0;
	};
} // namespace gargantua::render
