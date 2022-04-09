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
			//temporary.
			friend class FrameBuffer;

			inline void Create()
			{
				glGenTextures(1, &id);
			}

			inline void Destroy()
			{
				glDeleteTextures(1, &id);
				id = 0;
			}


			inline void Bind(natural_t slot = 0) const
			{
				glActiveTexture(GL_TEXTURE0 + slot);
				glBindTexture(GL_TEXTURE_2D, id);
			}

			inline void Unbind() const
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}


			/*
			Initialize the content of a texture with a file.
			*/
			bool Load(std::string_view file_name);

			/*
			Initialize an empty texture with the given dimensions.
			*/
			void Empty(natural_t width, natural_t height);

			/*
			Set a single color for the whole texture.
			*/
			void SetColor(void* data);
			void SetColor(natural_t x_offset, natural_t y_offset, natural_t width, natural_t height, void* data);
			//void SetColor(natural_t x, natural_t y, void* data);


			natural_t GetWidth() const noexcept
			{
				return width;
			}

			natural_t GetHeight() const noexcept
			{
				return height;
			}


		private:
			GLuint id = 0;
			natural_t width = 0;
			natural_t height = 0;
			GLenum data_format = 0;
		};
	} //namespace Renderer
} //namespace Gargantua