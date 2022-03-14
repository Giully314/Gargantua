#pragma once
/*
Gargantua/Renderer/Types.hpp

PURPOSE: Enums for defining various types.


CLASSES:
	DrawMode: specify the buffer draw mode.
	ShaderType: type of the shader.


DESCRIPTION:
	
*/

#include <glad/glad.h>


namespace Gargantua
{
	namespace Renderer
	{
		enum class DrawMode : GLenum
		{
			static_draw = GL_STATIC_DRAW,
			dynamic_draw = GL_DYNAMIC_DRAW,
		};


		enum class ShaderType : GLenum
		{
			fragment_shader = GL_FRAGMENT_SHADER,
			vertex_shader = GL_VERTEX_SHADER,
		};


		enum class BufferElementType : GLenum
		{
			float_t = GL_FLOAT,
			int_t = GL_INT,
			unsigned_int_t = GL_UNSIGNED_INT,
			unsigned_short_t = GL_UNSIGNED_SHORT,
		};


		struct Utility
		{
			static size_t ElementTypeSize(BufferElementType t)
			{
				switch (t)
				{
				case BufferElementType::float_t:
					return sizeof(GLfloat);
				case BufferElementType::int_t:
					return sizeof(GLint);
				case BufferElementType::unsigned_int_t:
					return sizeof(GLuint);
				case BufferElementType::unsigned_short_t:
					return sizeof(GLushort);
				}
				return 0;
			}
		};
	} //namespace Renderer 
} //namespace Gargantua