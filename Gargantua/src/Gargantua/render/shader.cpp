/*
gargantua/render/shader.cpp

*/

module;

#include <glad/glad.h>

module gargantua.render.shader;

import <string>;

import gargantua.system.resource_system;


namespace gargantua::render
{

	auto Shader::Compile(std::string_view path) -> void
	{
		/*GRG_CORE_DEBUG("Compile shader {}", path);*/

		std::string src = system::ResourceSystem::ReadFile(path);
		const char* p = src.data();

		glShaderSource(id, 1, &p, NULL);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			/*GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);*/

			// The maxLength includes the NULL character
			char info[512];
			GLsizei log_length;
			glGetShaderInfoLog(id, 512, &log_length, info);

			//GRG_CORE_ERROR("Shader {} compilation error {}, message: {}", path, result, info);
		}
	}

} //namespace gargantua::render