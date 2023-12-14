/*
* gargantua/render/render_framebuffer.cpp
*/

module;

#include <glad/glad.h>
#include <gargantua/log/logger_macro.hpp>

module gargantua.render.frame_buffer;

import gargantua.log.logger_system;

namespace gargantua::render
{
	auto FrameBuffer::Initialize(const u32 width, const u32 height) -> void
	{
		buffer.Empty(width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, id);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer.ID(), 0);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			GRG_CORE_ERROR("FrameBuffer not initialized: {}", status);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	auto FrameBuffer::Resize(const u32 width, const u32 height) -> void
	{
		Destroy(); //destroy frame buffer and the attached texture
		Create(); //create a new frame buffer and a new texture
		Initialize(width, height);
	}
} // namespace gargantua::render
