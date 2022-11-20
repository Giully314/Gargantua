/*
gargantua/render/texture2d.cpp
*/

module;

#include <glad/glad.h>
#include <stb_image/stb_image.h>

module gargantua.render.texture2d;


namespace gargantua::render
{

	auto Texture2d::Load(std::string_view file_name) -> void
	{
		//OpenGL start from the bottom to read the texture, so flip the image.
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* buffer = nullptr;
		integer_t twidth;
		integer_t theight;
		integer_t channels;

		buffer = stbi_load(file_name.data(), &twidth, &theight, &channels, 0);

		if (buffer)
		{
			info.width = twidth;
			info.height = theight;

			if (channels == 3)
			{
				info.data_format = GL_RGB;
			}
			else if (channels == 4)
			{
				info.data_format = GL_RGBA;
			}

			glBindTexture(GL_TEXTURE_2D, id);

			//specify what happens when the texture "finish" (repeat, mirror ecc)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//Specify what happens when the texture gets smaller or bigger
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, info.data_format, info.width, info.height, 0, info.data_format, GL_UNSIGNED_BYTE, buffer);

			stbi_image_free(buffer);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}


	auto Texture2d::Fill(void* data) -> void
	{
		Fill(0, 0, info.width, info.height, data);
	}


	auto Texture2d::Fill(natural_t x_offset, natural_t y_offset, natural_t width, natural_t height,
		void* data) -> void
	{
		glBindTexture(GL_TEXTURE_2D, id);

		glTexSubImage2D(GL_TEXTURE_2D, 0, x_offset, y_offset, width, height, info.data_format, GL_UNSIGNED_BYTE, data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}


	auto Texture2d::Empty(natural_t width, natural_t height) -> void
	{
		info.width = width;
		info.height = height;
		info.data_format = GL_RGBA;


		glBindTexture(GL_TEXTURE_2D, id);

		//specify what happens when the texture "finish" (repeat, mirror ecc)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Specify what happens when the texture gets smaller or bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, info.data_format, width, height, 0, info.data_format, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

} //namespace gargantua::render