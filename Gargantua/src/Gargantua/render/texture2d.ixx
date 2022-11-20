/*
gargantua/render/texture2d.ixx

PURPOSE: Wrapper class for OpenGL Texture.


CLASSES:
	Texture2dInfo: info for texture.
	Texture2d: Class for Texture object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.


USAGE:

*/

module;

#include <glad/glad.h>

export module gargantua.render.texture2d;

import <string_view>;

import gargantua.types;

import gargantua.render.opengl_object;


export namespace gargantua::render
{

	struct Texture2dInfo
	{
		natural_t width = 0;
		natural_t height = 0;
		GLenum data_format = 0;
	}; //struct Texture2dInfo


	class Texture2d : public OpenGLObject
	{
	public:
		auto Create() -> void
		{
			glGenTextures(1, &id);
		}

		auto Destroy() -> void
		{
			glDeleteTextures(1, &id);
			id = 0;
		}


		auto Bind(natural_t slot = 0) const -> void
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		auto Unbind() const -> void
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}


		/*
		Initialize the content of a texture with a file.
		*/
		auto Load(std::string_view file_name) -> void;

		/*
		Initialize an empty texture with the given dimensions.
		*/
		auto Empty(natural_t width, natural_t height) -> void;

		/*
		Set a single color for the whole texture.
		*/
		auto Fill(void* data) -> void;
		auto Fill(natural_t x_offset, natural_t y_offset, natural_t width, natural_t height, void* data) -> void;
		//void SetColor(natural_t x, natural_t y, void* data);




		auto GetWidth() const noexcept -> natural_t
		{
			return info.width;
		}

		auto GetHeight() const noexcept -> natural_t
		{
			return info.height;
		}


	private:
		Texture2dInfo info;
	}; //class Texture2d

} //namespace gargantua::render