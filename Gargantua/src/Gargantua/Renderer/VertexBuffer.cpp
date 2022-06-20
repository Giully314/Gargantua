/*
Gargantua/Renderer/VertexBuffer.cpp

*/

#include "VertexBuffer.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		void VertexBuffer::Load(const void* data, natural_t count, natural_t elem_per_vert, DrawMode mode)
		{
			info.elem_per_vert = elem_per_vert;
			info.draw_mode = mode;

			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, (GLenum)mode);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


	} //namespace Renderer 
} //namespace Gargantua