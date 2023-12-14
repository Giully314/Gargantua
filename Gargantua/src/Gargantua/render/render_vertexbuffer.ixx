/*
* gargantua/render/render_vertexbuffer.ixx
* 
* PURPOSE: Provide RAII implementation for opengl vertex buffer.
* 
* CLASSES:
*	VertexBuffer: class for opengl vertex buffer. 
*	VertexLayout: layout of a vertex element.
* 
* DESCRIPTION:
*	This component provides implementation of a wrapper for opengl vertex buffer object. A VertexBuffer can
*	keep only one type of data (could be position or color or texture coords). This approach simplifies 
*	implementation and data management.
*/

module;

#include <glad/glad.h>

export module gargantua.render.vertex_buffer;

import <span>;
import <concepts>;

import gargantua.types;
import gargantua.render.base_buffer;
import gargantua.render.render_info;

namespace gargantua::render
{
	// TODO: add concepts to Load() and SubLoad() methods.
	/*template <typename T>
	concept SupportedBufferData = std::same_as<f32, T> || std::same_as<typename T::value_type, f32>;*/

	export struct VertexLayout
	{
		constexpr explicit VertexLayout() = default;

		constexpr explicit VertexLayout(const u8 num_of_elements_, const u8 size_of_element_) : 
			num_of_elements(num_of_elements_), size_of_element(size_of_element_)
		{

		}

		/*
		* Return the vertex size in bytes.
		*/
		[[nodiscard]]
		constexpr auto GetVertexSize() const noexcept
		{
			return num_of_elements * size_of_element;
		}

		u8 num_of_elements = 0;
		u8 size_of_element = 0; // in bytes
	};

	export class VertexBuffer : public BaseBuffer
	{
	public:

		/*
		* Bind the vertex buffer.
		*/
		auto Bind() const -> void
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}


		/*
		* Unbind the vertex buffer.
		*/
		auto Unbind() const -> void
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


		/* Create a vertex buffer from data.
		*  data: span of float.
		*  num_of_elements: number of elements per vertex. Range from 1 to 4.
		*/
		template <typename T>
		auto Load(std::span<T> data, const u8 num_of_elements, const BufferDraw draw = BufferDraw::Static) -> void
		{
			BaseBuffer::Load(static_cast<const void*>(data.data()), data.size_bytes(), draw);
			layout = VertexLayout{ num_of_elements, sizeof(T) };
		}

		[[nodiscard]]
		auto Layout() const noexcept -> const VertexLayout&
		{
			return layout;
		}

		/*
		* Create an empty vertex buffer.	
		*/
		auto Empty(const u32 num_of_bytes, const BufferDraw draw = BufferDraw::Dynamic) -> void
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
