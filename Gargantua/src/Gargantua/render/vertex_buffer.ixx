/*
* gargantua/render/vertex_buffer.ixx
* 
* PURPOSE: vertex buffer object abstraction.
* 
* CLASSES:
*	VertexBuffer: abstraction of the VBO.
*	VertexLayout: layout of a vertex element.
* 
* DESCRIPTION:
*	To make things simple, for now, a single VBO contains only one type of data. Could be position, color and so on.
*	This simplify the registration to VAO.
*/

export module gargantua.render.buffer:vertex_buffer;
import :base_buffer;

import <span>;

import gargantua.types;

namespace gargantua::render
{
	export 
	struct VertexLayout
	{
		VertexLayout() = default;

		VertexLayout(u8 num_of_elements_, u8 size_of_element_) : num_of_elements(num_of_elements_), size_of_element(size_of_element_)
		{

		}

		// Return the vertex size in bytes.
		[[nodiscard]]
		constexpr auto GetVertexSize() const noexcept
		{
			return num_of_elements * size_of_element;
		}

		u8 num_of_elements = 0;
		u8 size_of_element = 0; // in bytes
	};

	export 
	class VertexBuffer : public BaseBuffer
	{
	public:
		// Create a vertex buffer from data. 
		// data: span of float.
		// num_of_elements: number of elements per vertex. Range from 1 to 4.
		auto Load(std::span<f32> data, u8 num_of_elements) -> void
		{
			BaseBuffer::Load(static_cast<void*>(data.data()), data.size_bytes());
			layout = VertexLayout{ num_of_elements, sizeof(f32) };
		}

		[[nodiscard]]
		auto GetLayout() const noexcept -> const VertexLayout&
		{
			return layout;
		}

	private:
		VertexLayout layout;
	};
} // namespace gargantua::render
