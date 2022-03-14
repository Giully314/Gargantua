#pragma once
/*
Gargantua/Renderer/Texture2d.hpp

PURPOSE: Wrapper class for OpenGL Texture.


CLASSES:
	Program: Class for Texture object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	


USAGE:
	
*/

#include <glad/glad.h>

#include "Gargantua/Types.hpp"


#include <string_view>

namespace Gargantua
{
	namespace Renderer
	{
		class Texture2d : private NonCopyable
		{
		public:
			inline void Create()
			{
				glGenTextures(1, &id);
			}

			inline void Destroy()
			{
				glDeleteTextures(1, &id);
				id = 0;
			}


			inline void Bind(natural_t slot = 0)
			{
				glActiveTexture(GL_TEXTURE0 + slot);
				glBindTexture(GL_TEXTURE_2D, id);
			}

			inline void Unbind()
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}



			void Load(std::string_view file_name);



		private:
			GLuint id = 0;
			natural_t width = 0;
			natural_t height = 0;
			GLenum data_format = 0;
		};
	} //namespace Renderer
} //namespace Gargantua