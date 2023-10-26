/*
* gargantua/render/shared.ixx
* 
* PURPOSE: Abstraction for OpenGL shader.
* 
* CLASSES:
*	Shader: Wrapper for an OpenGL shader.
* 
*/

module;

#include <gargantua/log/logger_macro.hpp>
#include <glad/glad.h>

export module gargantua.render.shader;

import <utility>;
import <string>;
import <string_view>;
import <stdexcept>;
import <filesystem>;

import gargantua.log.logger_system;
import gargantua.render.opengl_object;
import gargantua.resource.file_reader;

namespace gargantua::render
{

	export 
	enum class ShaderType
	{
		Vertex,
		Fragment,
		Null,
	};

	// Converts a ShaderType to the respective GLenum.
	auto ShaderTypeToGL(ShaderType type) -> GLenum
	{
		switch (type)
		{
		case ShaderType::Vertex:
			return GL_VERTEX_SHADER;
		case ShaderType::Fragment:
			return GL_FRAGMENT_SHADER;
		}

		// This should be unreachable.
		return GL_NONE;
	}


	export
	class Shader : public OpenGLObject
	{
	public:

		// Precondition: an opengl context must exist.
		Shader(std::filesystem::path filename, ShaderType type_) : type(type_)
		{
			id = glCreateShader(ShaderTypeToGL(type));

			if (auto source = resource::FileReader::ReadFile(filename); source)
			{
				const char* c = source->c_str();
				
				if (!Compile(c))
				{
					throw std::runtime_error{ "Error while compiling shader." };
				}
			} 
			else
			{
				throw std::invalid_argument{ "Error while loading file." };
			}
		}
		

		Shader(Shader&& other) noexcept : OpenGLObject(other.id)
		{
			other.id = 0;
		}

		auto operator=(Shader&& other) noexcept -> Shader&
		{
			if (&other != this)
			{
				Destroy();
				std::swap(id, other.id);
			}
			return *this;
		}

		~Shader()
		{
			Destroy();
		}
	
		auto Destroy() -> void
		{
			glDeleteShader(id);
			id = 0;
		}
	
	private:
		ShaderType type;

		auto Compile(const char* source_code) -> bool 
		{
			//GRG_CORE_DEBUG("Source code\n{}", source_code);
			glShaderSource(id, 1, &source_code, nullptr);
			glCompileShader(id);

			// check possible compilation errors.
			int  success;
			char info_log[512];
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(id, 512, nullptr, info_log);
				GRG_CORE_ERROR("Error compile shader. {}", info_log);

				return false;
			}
			return true;
		}
	};
} // namespace gargantua::render
