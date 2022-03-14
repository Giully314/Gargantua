/*
Gargantua/Renderer/Program.cpp
*/

#include "Program.hpp"

#include "Gargantua/Core/EngineLogger.hpp"


namespace Gargantua
{
	namespace Renderer
	{
		void Program::Link(NonOwnedRes<Shader> vert_shader, NonOwnedRes<Shader> frag_shader)
		{
			GRG_CORE_DEBUG("Linking shaders");

			glAttachShader(id, vert_shader->id);
			glAttachShader(id, frag_shader->id);
			glLinkProgram(id);

		
			int result;
			glValidateProgram(id);
			glGetProgramiv(id, GL_VALIDATE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GRG_CORE_ERROR("Program link error {}", result);
			}

			/*int success;
			char infoLog[512];
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(id, 512, NULL, infoLog);
				GRG_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED {}", infoLog);
			}*/
		}
	} //namespace Renderer 
} //namespace Gargantua