/*
* gargantua/render/program.ixx
* 
* PURPOSE: Abstraction for OpenGL program.
* 
* CLASSES:
*	Program: Manage an OpenGL program.
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
	export
	class Program : public OpenGLObject
	{
	public:
		// Precondition: an opengl context must exist.

		Program()
		{
			id = glCreateProgram();
		}

		Program(Shader& vertex_shader, Shader& fragment_shader)
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

		// Activate the program.
		auto Bind() const -> void
		{
			glUseProgram(id);
		}

		auto Unbind() const -> void
		{
			glUseProgram(0);
		}



		// Destroy the program.
		auto Destroy() -> void
		{
			glDeleteProgram(id);
			id = 0;
		}

		auto SetUniformArrayInt(std::string_view name, std::span<int> values)
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform1iv(location, values.size(), values.data());
		}


		auto SetUniform1f(std::string_view name, f32 v) const -> void
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
			glUniform2f(location, v[0], v[1]);
		}


		auto SetUniform3f(std::string_view name, f32 v0, f32 v1, f32 v2) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform3f(location, v0, v1, v2);
		}

		auto SetUniform3f(std::string_view name, const math::Vec3df& v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform3f(location, v[0], v[1], v[2]);
		}


		auto SetUniform4f(std::string_view name, f32 v0, f32 v1, f32 v2, f32 v3) const -> void
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


		auto SetUniform1i(std::string_view name, i32 v) const -> void
		{
			GLint location = glGetUniformLocation(id, name.data());
			glUniform1i(location, v);
		}


		auto LinkShaders(Shader& vertex_shader, Shader& fragment_shader) -> void
		{
			glAttachShader(id, vertex_shader.GetID());
			glAttachShader(id, fragment_shader.GetID());
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
	};
} // namespace gargantua::render
