#include "ElementBuffer.hpp"
/*
Gargantua/Renderer/ElementBuffer.cpp
*/


namespace Gargantua
{
	namespace Renderer
	{
		void ElementBuffer::Load(const void* data, natural_t count, BufferElementType type, DrawMode mode)
		{
			info.type = type;
			info.count = count;
			info.elem_per_vert = 0;
			info.draw_mode = mode;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * Conversion::ElementTypeSize(type), data, (GLenum)mode);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	} //namespace Renderer
} //namespace Gargantua