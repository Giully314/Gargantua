/*
* gargantua/render/vertex_array.ixx
* 
* PURPOSE: Manage vertex array using DSA.
* 
* CLASSES:
*	VertexArray:
* 
* DESCRIPTION:
*	
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

		auto Bind() -> void
		{
			glBindVertexArray(id);
		}

		auto Unbind() -> void
		{
			glBindVertexArray(0);
		}


		auto AddBuffer(const VertexBuffer& vbo, u32 idx) -> void
		{
			const auto& layout = vbo.GetLayout();
			glVertexArrayVertexBuffer(id, 0, vbo.GetID(), 0, layout.GetVertexSize());
			glEnableVertexArrayAttrib(id, idx);
			glVertexArrayAttribFormat(id, idx, layout.num_of_elements, GL_FLOAT, GL_FALSE, 0);
		}


		auto AddBuffer(const IndexBuffer& ibo) -> void
		{
			glVertexArrayElementBuffer(id, ibo.GetID());
		}

	private:
		auto Destroy() -> void
		{
			glDeleteVertexArrays(1, &id);
		}
	};

} // namespace gargantua::render