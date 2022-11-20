/*
gargantua/render/shader.ixx

PURPOSE: Wrapper class for OpenGL Shader.


CLASSES:
	Shader: Class for Shader object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A shader represent a single shader program (that is, a vertex shader, fragment shader and so on).
	This class is useful for the implementation of a cache system for the shaders to aauto recompiling them.
	Object of this class should be created by the associated manager to maximize performance for reuse.


USAGE:
	Shader vert;
	vert.Create();
	vert.Compile("vertex_shader_file.vert");
	...
	vert.Destroy();

	or better

	NonOwnedRes<Shader> s = shader_manager.Get("shader_name");
*/

module;

#include <glad/glad.h>

export module gargantua.render.shader;

import <string_view>;

import gargantua.types;
import gargantua.render.render_types;
import gargantua.render.opengl_object;


namespace gargantua::render
{

	export class Shader : public OpenGLObject
	{
	public:
		friend class Program;

		auto Create(ShaderType type) -> void
		{
			id = glCreateShader((GLenum)type);
		}

		auto Destroy() -> void
		{
			glDeleteShader(id);
			id = 0;
		}


		auto Compile(std::string_view path) -> void;
	}; //class Shader

} //namespace gargantua::render