#pragma once
/*
Gargantua/Renderer/Shader.hpp

PURPOSE: Wrapper class for OpenGL Shader.


CLASSES:
	Shader: Class for Shader object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A shader represent a single shader program (that is, a vertex shader, fragment shader and so on).
	This class is useful for the implementation of a cache system for the shaders to avoid recompiling them.
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

#include <glad/glad.h>

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/Types.hpp"
#include "Gargantua/Renderer/OpenGLObject.hpp"

#include <string_view>


namespace Gargantua
{
	namespace Renderer
	{
		class Shader : public OpenGLObject
		{
		public:
			friend class Program;

			inline void Create(ShaderType type)
			{
				id = glCreateShader((GLenum)type);
			}

			inline void Destroy()
			{
				glDeleteShader(id);
				id = 0;
			}


			void Compile(std::string_view path);
		};
	} //namespace Renderer
} //namespace Gargantua