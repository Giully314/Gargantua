/*
Gargantua/Renderer/VertexBuffer.cpp

*/

#include "VertexBuffer.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		void VertexBuffer::Load(const void* data, natural_t count, natural_t elem_per_vert, BufferElementType type, DrawMode mode)
		{
			info.type = type;
			info.count = count;
			info.elem_per_vert = elem_per_vert;
			info.draw_mode = mode;

			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, count * Conversion::ElementTypeSize(type), data, (GLenum)mode);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


	} //namespace Renderer 
} //namespace Gargantua