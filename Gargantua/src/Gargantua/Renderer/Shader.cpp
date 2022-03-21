/*
Gargantua/Renderer/Shader.cpp

*/

#include "Shader.hpp"

#include "Gargantua/Systems/ResourceSystem.hpp"
#include "Gargantua/Core/EngineLogger.hpp"

#include <string>

namespace Gargantua
{
	namespace Renderer
	{
		void Shader::Compile(std::string_view path)
		{
			GRG_CORE_DEBUG("Compile shader {}", path);

			std::string src = Systems::ResourceSystem::ReadFile(path);
			const char* p = src.data();

			glShaderSource(id, 1, &p, NULL);
			glCompileShader(id);

			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GRG_CORE_ERROR("Shader {} compilation error {}", path, result);
			}
		}
	} //namespace Renderer
} //namespace Gargantua