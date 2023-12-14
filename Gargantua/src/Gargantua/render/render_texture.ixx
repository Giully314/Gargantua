/*
* gargantua/render/render_texture.ixx
* 
* PURPOSE: Provide RAII implementation for opengl 2d texture.
* 
* CLASSES:
*	TextureInfo: info about the texture.
*	Texture: class wrapper for OpenGL texture.
* 
* TODO:
*	- allow the specification of interpolation.
*/

module;

#include <glad/glad.h>
#include <stb_image/stb_image.h>

export module gargantua.render.texture;

import <utility>;
import <string_view>;

import gargantua.types;
import gargantua.render.opengl_object;

namespace gargantua::render
{
	export struct TextureInfo
	{
		u32 width = 0;
		u32 height = 0;
		GLenum data_format = 0;
		GLenum internal_format = 0;
	};


	export class Texture : public OpenGLObject
	{
	public:

		/*
		* Precondition : an opengl context must exist.
		* Construct a new empty texture.
		*/
		explicit Texture();


		Texture(Texture&& other) : OpenGLObject(other.id)
		{
			other.id = 0;
		}

		auto operator=(Texture&& other) -> Texture&
		{
			if (&other != this)
			{
				Destroy();
				std::swap(id, other.id);
			}
			return *this;
		}

		~Texture()
		{
			Destroy();
		}

		/*
		* Bind the texture with the specified slot.
		*/
		auto Bind(u32 slot = 0) const -> void
		{
			/*glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, id);*/
			glBindTextureUnit(slot, id);
		}


		/*
		* Unbind the texture.
		*/
		auto Unbind() const -> void
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}


		/*
		* Load a texture from a file.
		* Precondition: the texture must not be in use. 
		*/
		auto Load(const std::string_view filename) -> void;


		/*
		* Create an empty texture with the specified width and height.
		*/
		auto Empty(const u32 width, const u32 height) -> void;
		

		// TODO: I don't like the void* data. Try something else in the interface.
		/*
		* Create a texture of size width, height and fill with data.
		* Precondition: the texture must not be in use. 
		* data: must be a pointer to data specified as unsigned int.
		*/
		auto Fill(const u32 width, const u32 height, const void *data) -> void;

		/*
		* Destroy the current texture.
		*/
		auto Destroy() -> void
		{
			glDeleteTextures(1, &id);
			id = 0;
			info.width = 0;
			info.height = 0;
			info.data_format = 0;
			info.internal_format = 0;
		}

		/*
		* Return texture info.
		*/
		constexpr auto Info() const noexcept -> const TextureInfo&
		{
			return info;
		}

		/*
		* Return the width of the texture.
		*/
		constexpr auto Width() const noexcept -> u32
		{
			return info.width;
		}


		/*
		* Return the height of the texture.
		*/
		constexpr auto Height() const noexcept -> u32
		{
			return info.height;
		}

	private:
		TextureInfo info;
	};
} // namespace gargantua::render
