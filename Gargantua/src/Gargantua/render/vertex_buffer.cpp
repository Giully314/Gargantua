/*
gargantua/render/vertex_buffer.cpp

*/

module;

#include <glad/glad.h>

module gargantua.render.vertex_buffer;


namespace gargantua::render
{

	auto VertexBuffer::Load(const void* data, natural_t count, natural_t elem_per_vert, DrawMode mode) -> void
	{
		info.elem_per_vert = elem_per_vert;
		info.draw_mode = mode;

		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, (GLenum)mode);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


} //namespace gargantua::render