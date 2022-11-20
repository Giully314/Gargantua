/*
gargantua/render/vertex_buffer.ixx

PURPOSE: Wrapper class for OpenGL VertexBuffer object.


CLASSES:
	VertexBufferInfo: info for the buffer.
	VertexBuffer: Class for VertexBuffer object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A buffer is just an array of data.
	For now the vertex buffer allows to load only floating point data.


USAGE:
	VertexBuffer vb;
	vb.Create();
	vb.Load(...);

	...

	vb.Destroy();
*/

module;

#include <glad/glad.h>

export module gargantua.render.vertex_buffer;

import gargantua.types;
import gargantua.render.render_types;
import gargantua.render.opengl_object;


export namespace gargantua::render
{

	struct VertexBufferInfo
	{
		natural_t elem_per_vert = 0;
		DrawMode draw_mode = DrawMode::static_draw;
	}; //struct VertexBufferInfo


	class VertexBuffer : public OpenGLObject
	{
	public:
		auto Create() -> void
		{
			glGenBuffers(1, &id);
		}

		auto Destroy() -> void
		{
			glDeleteBuffers(1, &id);
			id = 0;
		}

		auto Bind() const -> void
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		auto Unbind() const -> void
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}


		auto GetInfo() const noexcept -> const VertexBufferInfo&
		{
			return info;
		}


		/*
		The buffer is unbinded after the load of the data.
		*/
		auto Load(const void* data, natural_t count, natural_t elem_per_vert, DrawMode mode) -> void;


	private:
		VertexBufferInfo info;
	}; //class VertexBuffer

} //namespace gargantua::render