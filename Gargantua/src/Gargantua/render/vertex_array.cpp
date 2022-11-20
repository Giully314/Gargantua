/*
gargantua/render/vertex_array.cpp
*/

module;

#include <glad/glad.h>

module gargantua.render.vertex_array;


namespace gargantua::render
{
	
		auto VertexArray::AddVertexBuffer(const VertexBuffer& vb, natural_t attribute) -> void
		{
			glBindVertexArray(id);
			vb.Bind();

			const auto& info = vb.GetInfo();

			glEnableVertexAttribArray(attribute);
			glVertexAttribPointer(attribute, info.elem_per_vert, GL_FLOAT, GL_FALSE, 0, 0);
			glBindVertexArray(0);
		}


		auto VertexArray::AddElementBuffer(const ElementBuffer& eb) -> void
		{
			glBindVertexArray(id);
			eb.Bind();
			glBindVertexArray(0);
		}
	
} //namespace gargantua::render