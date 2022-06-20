#pragma once
/*
Gargantua/Renderer/Program.hpp

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
*/


#include <glad/glad.h>

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/Shader.hpp"
#include "Gargantua/Renderer/OpenGLObject.hpp"

#include "Gargantua/Math/Vec2d.hpp"
#include "Gargantua/Math/Vec3d.hpp"
#include "Gargantua/Math/Vec4d.hpp"
#include "Gargantua/Math/Mat4d.hpp"

#include <string_view>

namespace Gargantua
{
	namespace Renderer
	{

		//TODO: consider to make a cache for uniforms instaed of recomputing them.
		class Program : public OpenGLObject
		{
		public:
			inline void Create()
			{
				id = glCreateProgram();
			}

			inline void Destroy()
			{
				glDeleteProgram(id);
				id = 0;
			}

			inline void Bind() const
			{
				glUseProgram(id);
			}

			inline void Unbind() const
			{
				glUseProgram(0);
			}


			void Link(const Shader& vert_shader, const Shader& frag_shader);


			inline void SetUniform1f(std::string_view name, real_t v) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniform1f(location, v);
			}


			inline void SetUniform2f(std::string_view name, real_t v0, real_t v1) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniform2f(location, v0, v1);
			}

			inline void SetUniform2f(std::string_view name, const Math::Vec2df& v) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniform2f(location, v[0], v[1]);
			}


			inline void SetUniform3f(std::string_view name, real_t v0, real_t v1, real_t v2) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniform3f(location, v0, v1, v2);
			}

			inline void SetUniform3f(std::string_view name, const Math::Vec3df& v) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniform3f(location, v[0], v[1], v[2]);
			}


			inline void SetUniform4f(std::string_view name, real_t v0, real_t v1, real_t v2, real_t v3) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniform4f(location, v0, v1, v2, v3);
			}

			inline void SetUniform4f(std::string_view name, const Math::Vec4df& v) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniform4f(location, v[0], v[1], v[2], v[3]);
			}


			inline void SetUniformMatrix4f(std::string_view name, const Math::Mat4df& m) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniformMatrix4fv(location, 1, GL_TRUE, m.GetAddress());
			}


			inline void SetUniform1i(std::string_view name, integer_t v) const
			{
				GLint location = glGetUniformLocation(id, name.data());
				glUniform1i(location, v);
			}
		};
	} //namespace Renderer 
} //namespace Gargantua