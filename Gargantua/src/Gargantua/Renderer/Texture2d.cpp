/*
Gargantua/Renderer/Texture2d.cpp
*/

#include "Texture2d.hpp"

#include <stb_image/stb_image.h>


namespace Gargantua
{
	namespace Renderer
	{
		bool Texture2d::Load(std::string_view file_name)
		{
			stbi_set_flip_vertically_on_load(1);
			
			stbi_uc* buffer = nullptr;
			integer_t twidth;
			integer_t theight;
			integer_t channels;
			
			buffer = stbi_load(file_name.data(), &twidth, &theight, &channels, 0);

			if (buffer)
			{
				width = twidth;
				height = theight;

				if (channels == 3)
				{
					data_format = GL_RGB;
				}
				else if (channels == 4)
				{
					data_format = GL_RGBA;
				}

				glBindTexture(GL_TEXTURE_2D, id);

				//specify what happens when the texture "finish" (repeat, mirror ecc)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				//Specify what happens when the texture gets smaller or bigger
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, data_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, buffer);

				stbi_image_free(buffer);
				glBindTexture(GL_TEXTURE_2D, 0);

				return true;
			}

			return false;
		}


		void Texture2d::SetColor(void* data)
		{
			SetColor(0, 0, width, height, data);
		}


		void Texture2d::SetColor(natural_t x_offset, natural_t y_offset, natural_t width, natural_t height, void* data)
		{
			glBindTexture(GL_TEXTURE_2D, id);

			glTexSubImage2D(GL_TEXTURE_2D, 0, x_offset, y_offset, width, height, data_format, GL_UNSIGNED_BYTE, data);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		

		void Texture2d::Empty(natural_t width, natural_t height)
		{
			this->width = width;
			this->height = height;
			data_format = GL_RGBA;


			glBindTexture(GL_TEXTURE_2D, id);

			//specify what happens when the texture "finish" (repeat, mirror ecc)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//Specify what happens when the texture gets smaller or bigger
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, data_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, nullptr);

			glBindTexture(GL_TEXTURE_2D, 0);
		}


	} //namespace Renderer
} //namespace Gargantua