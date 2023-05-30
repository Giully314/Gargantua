/*
* gargantua/render/texture2d.cpp
*/

module;

#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <gargantua/log/logger_macro.hpp>

module gargantua.render.texture2d;

import gargantua.log.logger_system;


namespace gargantua::render
{
	Texture2d::Texture2d()
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &id);

		glBindTexture(GL_TEXTURE_2D, id);

		// Repeat along x axis.
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		// Repeat along y axis.
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		// Interpolation when rescaling.
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}


	auto Texture2d::Load(std::string_view filename) -> void
	{
		//OpenGL start from the bottom to read the texture, so flip the image.
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* buffer = nullptr;
		i32 twidth;
		i32 theight;
		i32 channels;

		buffer = stbi_load(filename.data(), &twidth, &theight, &channels, 0);

		if (buffer)
		{
			info.width = twidth;
			info.height = theight;

			if (channels == 3)
			{
				info.data_format = GL_RGB;
				info.internal_format = GL_RGB8;
			}
			else if (channels == 4)
			{
				info.data_format = GL_RGBA;
				info.internal_format = GL_RGBA8;
			}


			glTextureStorage2D(id, 1, info.internal_format, info.width, info.height);

			glTextureSubImage2D(id, 0, 0, 0, info.width, info.height, info.data_format, GL_UNSIGNED_BYTE, buffer);

			/*Bind();
			glGenerateMipmap(GL_TEXTURE_2D);
			Unbind();*/

			stbi_image_free(buffer);
		}
		else
		{
			GRG_CORE_ERROR("Texture not loaded! Filename: {}", filename);
		}
	}


	auto Texture2d::Empty(u32 width, u32 height) -> void
	{
		info.width = width;
		info.height = height;
		info.data_format = GL_RGBA;
		info.internal_format = GL_RGBA8;
		glTextureStorage2D(id, 1, info.internal_format, info.width, info.height);
	}


	auto Texture2d::Fill(u32 width, u32 height, void* data) -> void
	{
		// First create an empty texture.
		info.width = width;
		info.height = height;
		info.data_format = GL_RGBA;
		info.internal_format = GL_RGBA8;

		glBindTexture(GL_TEXTURE_2D, id);

		glTexImage2D(GL_TEXTURE_2D, 0, info.data_format, width, height, 0, info.data_format, GL_UNSIGNED_BYTE, data);
	}

} // namespace gargantua::render
