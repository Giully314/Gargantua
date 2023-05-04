/*
* gargantua/render/index_buffer.ixx
* 
* PURPOSE: Element buffer object abstraction.
*	
* CLASSES:
*	IndexBuffer: abstraction of the EBO.
* 
* DESCRIPTION:
*	Stores the information about the indexes of the vertecies to be used during draw.
*/

export module gargantua.render.buffer:index_buffer;
import :base_buffer;

import <span>;

import gargantua.types;
import gargantua.render.render_info;

namespace gargantua::render
{
	export
	class IndexBuffer : public BaseBuffer
	{
	public:
		auto Load(std::span<u32> data, BufferDraw draw = BufferDraw::Static) -> void
		{
			BaseBuffer::Load(static_cast<void*>(data.data()), data.size_bytes(), draw);
			index_count = data.size();
		}

		auto GetCount() const noexcept -> u32
		{
			return index_count;
		}

	private:
		u32 index_count = 0;
	};
} // namespace gargantua::render
