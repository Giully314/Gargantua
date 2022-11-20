/*
gargantua/render/program.cpp
*/

module;

#include <glad/glad.h>

module gargantua.render.program;

namespace gargantua::render
{

	auto Program::Link(const Shader& vert_shader, const Shader& frag_shader) -> void
	{
		//GRG_CORE_DEBUG("Linking shaders");

		glAttachShader(id, vert_shader.GetRenderId());
		glAttachShader(id, frag_shader.GetRenderId());
		glLinkProgram(id);


		/*int result;
		glValidateProgram(id);
		glGetProgramiv(id, GL_VALIDATE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GRG_CORE_ERROR("Program link error {}", result);
		}*/

		//THIS VERSION ONLY FOR DEBUG PURPOSE IN DEVELOPMENT PROCESS
		int success;
		char infoLog[512];
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, nullptr, infoLog);
			//GRG_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED {}", infoLog);
		}
	}

} //namespace gargantua::render