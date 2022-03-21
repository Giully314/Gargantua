/*
Gargantua/Renderer/VertexArray.cpp
*/

#include "VertexArray.hpp"


namespace Gargantua
{
	namespace Renderer
	{
		void VertexArray::AddVertexBuffer(const VertexBuffer& vb, natural_t attribute)
		{
			glBindVertexArray(id);
			vb.Bind();

			const auto& info = vb.GetInfo();

			glEnableVertexAttribArray(attribute);
			glVertexAttribPointer(attribute, info.elem_per_vert, (GLenum)info.type, GL_TRUE, 0, 0);
		}


		void VertexArray::AddElementBuffer(const ElementBuffer& eb)
		{
			glBindVertexArray(id);
			eb.Bind();
		}
	} //namespace Renderer 
} //namespace Gargantua