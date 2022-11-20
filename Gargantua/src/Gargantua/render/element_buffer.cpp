/*
gargantua/render/element_buffer.cpp
*/

module;

#include <glad/glad.h>

module gargantua.render.element_buffer;

namespace gargantua::render
{

	auto ElementBuffer::Load(const void* data, natural_t count, DrawMode mode) -> void
	{
		info.count = count;
		info.draw_mode = mode;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, (GLenum)mode);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} //namespace gargantua::render