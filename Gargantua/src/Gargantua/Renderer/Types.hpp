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
	} //namespace Renderer 
} //namespace Gargantua