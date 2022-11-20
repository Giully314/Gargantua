/*
gargantua/render/program.ixx

PURPOSE: Wrapper class for OpenGL Program.


CLASSES:
	Program: Class for Program object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A Program object is composed of 2 shaders: a vertex shader and a fragment shader.
	It allows to set uniforms (better to do this through a Material class).


USAGE:
	Program p;
	p.Create();
	p.Link(vert, frag);
	p.Bind();
	p.SetUniformFloat("my_uniform", 3.14.f);


TODO: 
	-consider to make a cache for uniforms instaed of recomputing them.
*/

module;

#include <glad/glad.h>

export module gargantua.render.program;

import <string_view>;

import gargantua.types;

import gargantua.render.opengl_object;
import gargantua.render.shader;

import gargantua.math.vector;
import gargantua.math.mat4d;



namespace gargantua::render
{

	export class Program : public OpenGLObject
	{
	public:
		auto Create() -> void
		{
			id = glCreateProgram();
		}

		auto Destroy() -> void
		{
			glDeleteProgram(id);
			id = 0;
		}

		auto Bind() const -> void
		{
			glUseProgram(id);
		}

		auto Unbind() const -> void
		{
			glUseProgram(0);
		}


		auto Link(const Shader& vert_shader, const Shader& frag_shader) -> void;


		auto SetUniform1f(std::string_view name, real_t v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform1f(location, v);
		}


		auto SetUniform2f(std::string_view name, real_t v0, real_t v1) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform2f(location, v0, v1);
		}

		auto SetUniform2f(std::string_view name, const math::Vec2df& v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform2f(location, v[0], v[1]);
		}


		auto SetUniform3f(std::string_view name, real_t v0, real_t v1, real_t v2) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform3f(location, v0, v1, v2);
		}

		auto SetUniform3f(std::string_view name, const math::Vec3df& v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform3f(location, v[0], v[1], v[2]);
		}


		auto SetUniform4f(std::string_view name, real_t v0, real_t v1, real_t v2, real_t v3) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform4f(location, v0, v1, v2, v3);
		}

		auto SetUniform4f(std::string_view name, const math::Vec4df& v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform4f(location, v[0], v[1], v[2], v[3]);
		}


		auto SetUniformMatrix4f(std::string_view name, const math::Mat4df& m) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniformMatrix4fv(location, 1, GL_TRUE, m.GetAddress());
		}


		auto SetUniform1i(std::string_view name, integer_t v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform1i(location, v);
		}
	}; //class Program

} //namespace gargantua::render