/*
* gargantua/render/vertex_array.ixx
* 
* PURPOSE: Abstraction for OpenGL vertex array.
* 
* CLASSES:
*	VertexArray: Manage vertex array.
*/

module;

#include <glad/glad.h>

export module gargantua.render.vertex_array;

import <utility>;

import gargantua.types;
import gargantua.render.opengl_object;
import gargantua.render.buffer;

namespace gargantua::render
{
	export
	class VertexArray : public OpenGLObject
	{
	public:
		VertexArray()
		{
			glCreateVertexArrays(1, &id);
		}

		VertexArray(VertexArray&& other) noexcept : OpenGLObject(other.id)
		{
			other.id = 0;
		}

		[[nodiscard]]
		auto operator=(VertexArray&& other) noexcept -> VertexArray&
		{
			if (&other != this)
			{
				Destroy();
				std::swap(id, other.id);
			}
			return *this;
		}


		~VertexArray()
		{
			Destroy();
		}

		auto Bind() const -> void
		{
			glBindVertexArray(id);
		}

		auto Unbind() const -> void
		{
			glBindVertexArray(0);
		}


		auto AddBuffer(const VertexBuffer& vbo, u32 idx) -> void
		{
			const auto& layout = vbo.GetLayout();
			/*glEnableVertexArrayAttrib(id, idx);
			glVertexArrayVertexBuffer(id, 0, vbo.GetID(), 0, layout.GetVertexSize());
			glVertexArrayAttribFormat(id, idx, layout.num_of_elements, GL_FLOAT, GL_FALSE, 0);
			glVertexArrayAttribBinding(id, idx, 0);*/
			glBindVertexArray(id);
			vbo.Bind();

			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx, layout.num_of_elements, GL_FLOAT, GL_FALSE, 0, 0);
			glBindVertexArray(0);
		}


		auto AddBuffer(const IndexBuffer& ibo) -> void
		{
			glVertexArrayElementBuffer(id, ibo.GetID());
			index_count = ibo.GetCount();
		}


		auto GetCount() const noexcept -> u32
		{
			return index_count;
		}


	private:
		auto Destroy() -> void
		{
			glDeleteVertexArrays(1, &id);
		}

	private:
		u32 index_count = 0;
	};
} // namespace gargantua::render