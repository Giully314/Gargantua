#include "ElementBuffer.hpp"
/*
Gargantua/Renderer/ElementBuffer.cpp
*/


namespace Gargantua
{
	namespace Renderer
	{
		void ElementBuffer::Load(const void* data, natural_t count, DrawMode mode)
		{
			info.count = count;
			info.draw_mode = mode;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, (GLenum)mode);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	} //namespace Renderer
} //namespace Gargantua