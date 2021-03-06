#pragma once
/*
Gargantua/Renderer/VertexArray.hpp

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

#include <glad/glad.h>

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/OpenGLObject.hpp"
#include "Gargantua/Renderer/VertexBuffer.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"


namespace Gargantua
{
	namespace Renderer
	{
		class VertexArray : public OpenGLObject
		{
		public:
			void Create()
			{
				glGenVertexArrays(1, &id);
			}

			void Destroy()
			{
				glDeleteVertexArrays(1, &id);
				id = 0;
			}

			void Bind() const
			{
				glBindVertexArray(id);
			}

			void Unbind() const
			{
				glBindVertexArray(0);
			}


			void AddVertexBuffer(const VertexBuffer& vb, natural_t attribute);

			void AddElementBuffer(const ElementBuffer& eb);
		};
	} //namespace Renderer 
} //namespace Gargantua