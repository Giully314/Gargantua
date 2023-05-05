/*
* gargantua/render/texture.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* 
* TODO:
*	- allow the specification of interpolation.
*/

module;

#include <glad/glad.h>
#include <stb_image/stb_image.h>

export module gargantua.render.texture2d;

import <utility>;
import <string_view>;

import gargantua.types;
import gargantua.render.opengl_object;

namespace gargantua::render
{
	export 
	struct Texture2dInfo
	{
		u32 width = 0;
		u32 height = 0;
		GLenum data_format = 0;
		GLenum internal_format = 0;
	};


	export
	class Texture2d : public OpenGLObject
	{
	public:

		// Precondition: an opengl context must exist.
		Texture2d();


		Texture2d(Texture2d&& other) : OpenGLObject(other.id)
		{
			other.id = 0;
		}

		auto operator=(Texture2d&& other) -> Texture2d&
		{
			if (&other != this)
			{
				Destroy();
				std::swap(id, other.id);
			}
			return *this;
		}

		~Texture2d()
		{
			Destroy();
		}


		auto Bind(u32 slot = 0) const -> void
		{
			/*glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, id);*/
			glBindTextureUnit(slot, id);
		}


		auto Unbind() const -> void
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}


		// Load a texture from a file.
		// Precondition: the texture must not be in use. 
		auto Load(std::string_view filename) -> void;


		auto Empty(u32 width, u32 height) -> void;
		
		// TODO: i don't like the void* data. Try something else in the interface.
		// Create a texture of size width, height and fill with data.
		// Precondition: the texture must not be in use. 
		// data: must be a pointer to data specified as unsigned int.
		auto Fill(u32 width, u32 height, void *data) -> void;


		auto Destroy() -> void
		{
			glDeleteTextures(1, &id);
			id = 0;
		}


		auto GetInfo() const noexcept -> const Texture2dInfo&
		{
			return info;
		}

	private:
		Texture2dInfo info;
	};
} // namespace gargantua::render
