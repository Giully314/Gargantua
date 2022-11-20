/*
gargantua/render/frame_buffer.cpp
*/

module;

#include <glad/glad.h>

module gargantua.render.frame_buffer;


namespace gargantua::render
{

	auto FrameBuffer::Initialize(natural_t width, natural_t height) -> void
	{
		buffer.Create();
		buffer.Empty(width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, id);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer.GetRenderId(), 0);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			//GRG_CORE_ERROR("FrameBuffer not initialized: {}", status);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	auto FrameBuffer::Resize(natural_t width, natural_t height) -> void
	{
		Destroy(); //destroy frame buffer and the attached texture
		Create(); //create a new frame buffer
		Initialize(width, height);
	}

} //namespace gargantua::render