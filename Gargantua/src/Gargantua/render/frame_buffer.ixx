/*
* gargantua/render/frame_buffer.ixx
* 
* PURPOSE: Abstraction for OpenGL frame buffer.
* 
* CLASSES:
*	FrameBuffer: Manage an OpenGL frame buffer.
*/

module;

#include <glad/glad.h>

export module gargantua.render.frame_buffer;

import gargantua.types;
import gargantua.render.opengl_object;
import gargantua.render.texture2d;


namespace gargantua::render
{
	export 
	class FrameBuffer : public OpenGLObject
	{
	public:
		FrameBuffer()
		{
			glGenFramebuffers(1, &id);
		}
		
		~FrameBuffer()
		{
			Destroy();
		}

		auto Destroy() -> void
		{
			glDeleteFramebuffers(1, &id);
			id = 0;
			buffer.Destroy();
		}


		auto Bind() const -> void
		{
			glBindFramebuffer(GL_FRAMEBUFFER, id);
		}

		auto Unbind() const -> void
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}


		auto Initialize(u32 width, u32 height) -> void;

		auto Resize(u32 width, u32 height) -> void;


		auto GetColorBuffer() -> Texture2d&
		{
			return buffer;
		}


		auto GetBufferId() const -> render_id_t
		{
			return buffer.GetID();
		}


		auto GetHeight() const noexcept -> u32
		{
			return buffer.GetInfo().height;
		}

		auto GetWidth() const noexcept -> u32
		{
			return buffer.GetInfo().width;
		}

	private:
		// Precondition: must be called only after a Destroy().
		auto Create() -> void
		{
			glGenFramebuffers(1, &id);
			buffer = Texture2d();
		}

	private:
		Texture2d buffer;
	}; 

} // namespace gargantua::render
