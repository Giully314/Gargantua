/*
* gargantua/render/render_program.ixx
* 
* PURPOSE: Provide RAII implementation for OpenGL program.
* 
* CLASSES:
*	Program: class for opengl program.
* 
* DESCRIPTION:
*	This component provides a class to manage an opengl program created using two shaders. It access uniforms
*	
* 
* TODO:
*	- cache the uniform?
*/

module;

#include <gargantua/log/logger_macro.hpp>
#include <glad/glad.h>

export module gargantua.render.program;

import <span>;
import <utility>;
import <string_view>;

import gargantua.log.logger_system;
import gargantua.math.matrix;
import gargantua.math.vector;
import gargantua.render.opengl_object;
import gargantua.render.shader;

namespace gargantua::render
{
	export class Program : public OpenGLObject
	{
	public:
		/*
		* Create an empty program.
		* Precondition: an opengl context must exist.
		*/
		explicit Program()
		{
			id = glCreateProgram();
		}


		/*
		* Create a program by linking a vertex shader and a fragment shader.
		* Precondition: an opengl context must exist.
		* Precondition: the shaders must be in a well formed state.
		*/
		explicit Program(Shader& vertex_shader, Shader& fragment_shader)
		{
			id = glCreateProgram();
			LinkShaders(vertex_shader, fragment_shader);
		}


		Program(Program&& other) noexcept : OpenGLObject(other.id)
		{
			other.id = 0;
		}

		auto operator=(Program&& other) noexcept -> Program&
		{
			if (&other != this)
			{
				Destroy();
				std::swap(id, other.id);
			}
			return *this;
		}

		~Program()
		{
			Destroy();
		}

		/*
		* Bind the program for drawing.
		*/
		auto Bind() const -> void
		{
			glUseProgram(id);
		}


		/*
		* Unbind the program.
		*/
		auto Unbind() const -> void
		{
			glUseProgram(0);
		}



		/*
		* Destroy the program.
		*/
		auto Destroy() -> void
		{
			glDeleteProgram(id);
			id = 0;
		}


		/*
		* Link two shaders to make a program.
		* Precondition: program must be in an empty state.
		*/
		auto LinkShaders(Shader& vertex_shader, Shader& fragment_shader) -> void
		{
			glAttachShader(id, vertex_shader.ID());
			glAttachShader(id, fragment_shader.ID());
			glLinkProgram(id);

			// check possible link errors.
			int  success;
			char info_log[512];
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(id, 512, nullptr, info_log);
				GRG_CORE_ERROR("Error linking program. {}", info_log);

				// TODO: set an invalid state.
			}
		}


		// *********************** SET UNIFORMS ************************************
		
		auto SetUniformArrayInt(const std::string_view name, std::span<int> values) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform1iv(location, values.size(), values.data());
		}


		auto SetUniform1f(const std::string_view name, f32 v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform1f(location, v);
		}


		auto SetUniform2f(std::string_view name, f32 v0, f32 v1) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform2f(location, v0, v1);
		}

		auto SetUniform2f(std::string_view name, const math::Vec2df& v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform2f(location, v.x, v.y);
		}


		auto SetUniform3f(std::string_view name, f32 v0, f32 v1, f32 v2) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform3f(location, v0, v1, v2);
		}

		auto SetUniform3f(std::string_view name, const math::Vec3df& v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform3f(location, v.x, v.y, v.z);
		}


		auto SetUniform4f(std::string_view name, f32 v0, f32 v1, f32 v2, f32 v3) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform4f(location, v0, v1, v2, v3);
		}

		auto SetUniform4f(std::string_view name, const math::Vec4df& v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform4f(location, v.x, v.y, v.z, v.w);
		}


		auto SetUniformMatrix4f(std::string_view name, const math::Mat4df& m) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniformMatrix4fv(location, 1, GL_TRUE, m.GetAddress());
		}


		auto SetUniform1i(std::string_view name, i32 v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform1i(location, v);
		}
	};
} // namespace gargantua::render
