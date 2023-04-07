/*
* gargantua/render/program.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* 
*/

module;

#include <gargantua/log/logger_macro.hpp>
#include <glad/glad.h>

export module gargantua.render.program;

import <utility>;

import gargantua.logging.logger_system;
import gargantua.render.opengl_object;
import gargantua.render.shader;

namespace gargantua::render
{
	export
	class Program : public OpenGLObject
	{
	public:
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
		auto Use() -> void
		{
			glUseProgram(id);
		}

		// Destroy the program.
		auto Destroy() -> void
		{
			glDeleteProgram(id);
			id = 0;
		}

	private:

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
