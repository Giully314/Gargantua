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

namespace gargantua::render
{
	export
	class IndexBuffer : public BaseBuffer
	{
	public:
		auto Load(std::span<u32> data) -> void
		{
			BaseBuffer::Load(static_cast<void*>(data.data()), data.size_bytes());
		}
	};
} // namespace gargantua::render
