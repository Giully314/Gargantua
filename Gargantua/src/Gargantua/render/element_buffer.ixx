/*
gargantua/render/element_buffer.ixx

PURPOSE: Wrapper class for OpenGL ElementBuffer object.


CLASSES:
	ElementBufferInfo: info for the buffer.
	ElementBuffer: Class for ElementBuffer object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A buffer is just an array of data.
	For now the element buffer loads only unsigned short indices.
*/

module;

#include <glad/glad.h>

export module gargantua.render.element_buffer;

import gargantua.types;
import gargantua.render.render_types;
import gargantua.render.opengl_object;


export namespace gargantua::render
{

	struct ElementBufferInfo
	{
		natural_t count = 0;
		DrawMode draw_mode = DrawMode::static_draw;
	}; //struct ElementBufferInfo


	class ElementBuffer : public OpenGLObject
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
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}

		auto Unbind() const -> void
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}



		auto GetCount() const noexcept -> natural_t
		{
			return info.count;
		}

		auto GetInfo() const noexcept -> const ElementBufferInfo&
		{
			return info;
		}


		auto Load(const void* data, natural_t count, DrawMode mode) -> void; 


	private:
		ElementBufferInfo info;
	}; //class ElementBuffer

} //namespace gargantua::render