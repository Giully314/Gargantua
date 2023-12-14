/*
* gargantua/render/render_framebuffer.ixx
* 
* PURPOSE: Provide RAII implementation for opengl frame buffer.
* 
* CLASSES:
*	FrameBuffer: Manage an OpenGL frame buffer.
*/

module;

#include <glad/glad.h>

export module gargantua.render.frame_buffer;

import gargantua.types;
import gargantua.render.opengl_object;
import gargantua.render.texture;


namespace gargantua::render
{
	export class FrameBuffer : public OpenGLObject
	{
	public:
		/*
		* Construct a frame buffer.
		* Precondition: an opengl context must exist.
		*/
		explicit FrameBuffer()
		{
			glGenFramebuffers(1, &id);
		}
		
		~FrameBuffer()
		{
			Destroy();
		}

		/*
		* Destroy the frame buffer and the texture attached to it.
		*/
		auto Destroy() -> void
		{
			glDeleteFramebuffers(1, &id);
			id = 0;
			buffer.Destroy();
		}


		/*
		* Bind the frame buffer.
		*/
		auto Bind() const -> void
		{
			glBindFramebuffer(GL_FRAMEBUFFER, id);
		}


		/*
		* Unbind the frame buffer.
		*/
		auto Unbind() const -> void
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}


		/*
		* Initialize an empty frame buffer.
		*/
		auto Initialize(const u32 width, const u32 height) -> void;


		/*
		* Resize the frame buffer.
		*/
		auto Resize(const u32 width, const u32 height) -> void;


		/*
		* Get the texture attached to the frame buffer.
		*/
		auto ColorBuffer() -> Texture&
		{
			return buffer;
		}


		/*
		* Get the id of the texture attached to the frame buffer.
		*/
		auto BufferID() const -> render_id_t
		{
			return buffer.ID();
		}


		/*
		* Get the height of the frame buffer.
		*/
		auto Height() const noexcept -> u32
		{
			return buffer.Height();
		}

		/*
		* Get the width of the frame buffer.
		*/
		auto Width() const noexcept -> u32
		{
			return buffer.Width();
		}

	private:
		// Precondition: must be called only after a Destroy().
		auto Create() -> void
		{
			glGenFramebuffers(1, &id);
			buffer = Texture();
		}

	private:
		Texture buffer;
	}; 

} // namespace gargantua::render
