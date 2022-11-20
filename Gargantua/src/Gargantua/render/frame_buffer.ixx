/*
gargantua/render/frame_buffer.ixx

PURPOSE:

CLASSES:

DESCRIPTION:


TODO:
	I don't like the way i manage the buffer inside Create and Destroy();

*/

module;

#include <glad/glad.h>

export module gargantua.render.frame_buffer;

import gargantua.types;
import gargantua.render.opengl_object;
import gargantua.render.texture2d;



namespace gargantua::render
{

	export class FrameBuffer : public OpenGLObject
	{
	public:
		auto Create() -> void
		{
			glGenFramebuffers(1, &id);
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


		auto Initialize(natural_t width, natural_t height) -> void;

		auto Resize(natural_t width, natural_t height) -> void;


		auto GetColorBuffer() -> Texture2d&
		{
			return buffer;
		}


		auto GetColorBufferId() const -> render_id_t
		{
			return buffer.GetRenderId();
		}


		auto GetHeight() const noexcept -> natural_t
		{
			return buffer.GetHeight();
		}

		auto GetWidth() const noexcept -> natural_t
		{
			return buffer.GetWidth();
		}

	private:
		Texture2d buffer;
	}; //class FrameBuffer

} //namespace gargantua::render
