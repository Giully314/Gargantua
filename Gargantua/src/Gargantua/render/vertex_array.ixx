/*
gargantua/render/vertex_array.ixx

PURPOSE: Wrapper class for OpenGL VertexArray object.


CLASSES:
	VertexArray: Class for VertexArray object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	VertexArray is a collection of VertexBuffer. There is no layout because this implementation
	support only (for now) VertexBuffer of one type of element.

TODO:
	add an header file for both shader program and vertex array to specify, using define directives,
	location, texture and normals.
	For example:

	#define LOCATION 0
	#define TEXTURE 1

*/

module;

#include <glad/glad.h>

export module gargantua.render.vertex_array;

import gargantua.types;
import gargantua.render.opengl_object;
import gargantua.render.element_buffer;
import gargantua.render.vertex_buffer;


namespace gargantua::render
{

	export class VertexArray : public OpenGLObject
	{
	public:
		auto Create() -> void
		{
			glGenVertexArrays(1, &id);
		}

		auto Destroy() -> void
		{
			glDeleteVertexArrays(1, &id);
			id = 0;
		}

		auto Bind() const -> void
		{
			glBindVertexArray(id);
		}

		auto Unbind() const -> void
		{
			glBindVertexArray(0);
		}


		auto AddVertexBuffer(const VertexBuffer& vb, natural_t attribute) -> void;

		auto AddElementBuffer(const ElementBuffer& eb) -> void;
	}; //class VertexArray

} //namespace gargantua::render
