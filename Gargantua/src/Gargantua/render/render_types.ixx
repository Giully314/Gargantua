/*
gargantua/render/render_types.ixx

PURPOSE: Enums for defining various types.


CLASSES:
	DrawMode: specify the buffer draw mode.
	ShaderType: type of the shader.


DESCRIPTION:

*/

module;

#include <glad/glad.h>

export module gargantua.render.render_types;



export namespace gargantua::render
{

	enum class DrawMode : GLenum
	{
		static_draw = GL_STATIC_DRAW,
		dynamic_draw = GL_DYNAMIC_DRAW,
	}; //enum class DrawMode


	enum class ShaderType : GLenum
	{
		fragment_shader = GL_FRAGMENT_SHADER,
		vertex_shader = GL_VERTEX_SHADER,
	}; //enum class ShaderType

} //namespace gargantua::render