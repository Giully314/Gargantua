/*
* gargantua/render/render_vertexarray.ixx
* 
* PURPOSE: Provide RAII implementation for opengl vertex array.
* 
* CLASSES:
*	VertexArray: class for opengl vertex array.
* 
* DESCRIPTION:
*	This component provides implementation of a wrapper for opengl vertex array. The class VertexArray supports 
*	adding EBO and VBO (with restriction specified in the vertex_buffer component).
* 
* USAGE:
*	VertexBuffer vbo1;
*	VertexBuffer vbo2; 
*	IndexBuffer ibo1;
* 
*	// Load data into vbo and ebo.
*	
*	VertexArray vao;
*	vao.AddBuffer(vbo1, 0); // idx passed is the same as the one used in the shader program.
*	vao.AddBuffer(vbo2, 1);
*	vao.AddBuffer(ibo1);
*/

module;

#include <glad/glad.h>

export module gargantua.render.vertex_array;

import <utility>;

import gargantua.types;
import gargantua.render.opengl_object;
import gargantua.render.vertex_buffer;
import gargantua.render.index_buffer;


namespace gargantua::render
{
	export class VertexArray : public OpenGLObject
	{
	public:
		/*
		* Create a vertex array.
		* Precondition: an opengl context must exist.
		*/
		explicit VertexArray()
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


		/*
		* Bind the vertex array.
		*/
		auto Bind() const -> void
		{
			glBindVertexArray(id);
		}


		/*
		* Unbind the vertex array.
		*/
		auto Unbind() const -> void
		{
			glBindVertexArray(0);
		}


		/*
		* Add a vertex buffer with attribute array idx.
		*/
		auto AddBuffer(const VertexBuffer& vbo, u32 idx) -> void
		{
			const auto& layout = vbo.Layout();
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


		/*
		* Add an index buffer.
		*/
		auto AddBuffer(const IndexBuffer& ibo) -> void
		{
			glVertexArrayElementBuffer(id, ibo.ID());
			index_count = ibo.Count();
		}


		/*
		* Get the number of indices.
		*/
		auto Count() const noexcept -> u32
		{
			return index_count;
		}


		/*
		* Destroy the vertex array.
		*/
		auto Destroy() -> void
		{
			glDeleteVertexArrays(1, &id);
		}

	private:
		u32 index_count = 0;
	};
} // namespace gargantua::render