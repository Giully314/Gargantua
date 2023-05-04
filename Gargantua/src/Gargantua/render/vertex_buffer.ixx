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

module;

#include <glad/glad.h>

export module gargantua.render.buffer:vertex_buffer;
import :base_buffer;

import <span>;

import gargantua.types;
import gargantua.render.render_info;

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

		auto Bind() const -> void
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		auto Unbind() const -> void
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


		// Create a vertex buffer from data. 
		// data: span of float.
		// num_of_elements: number of elements per vertex. Range from 1 to 4.
		template <typename T> 
		auto Load(std::span<T> data, u8 num_of_elements, BufferDraw draw = BufferDraw::Static) -> void
		{
			BaseBuffer::Load(static_cast<void*>(data.data()), data.size_bytes(), draw);
			layout = VertexLayout{ num_of_elements, sizeof(T) };
		}

		[[nodiscard]]
		auto GetLayout() const noexcept -> const VertexLayout&
		{
			return layout;
		}

		// Create an empty vertex buffer 
		auto Empty(u32 num_of_bytes, BufferDraw draw = BufferDraw::Dynamic) -> void
		{
			BaseBuffer::Load(nullptr, num_of_bytes, draw);
		}


		template <typename T>
		auto LoadSubData(std::span<T> data)
		{
			BaseBuffer::LoadSubData(static_cast<void*>(data.data()), data.size_bytes());
		}


		auto SetLayout(VertexLayout layout) -> void
		{
			this->layout = layout;
		}

	private:
		VertexLayout layout;
	};
} // namespace gargantua::render
