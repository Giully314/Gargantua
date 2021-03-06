/*
Gargantua/Renderer/FrameBuffer.cpp
*/
#include "FrameBuffer.hpp"

#include "Gargantua/Core/EngineLogger.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		void FrameBuffer::Initialize(natural_t width, natural_t height)
		{
			buffer.Create();
			buffer.Empty(width, height);

			glBindFramebuffer(GL_FRAMEBUFFER, id);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer.GetRenderId(), 0);

			GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (status != GL_FRAMEBUFFER_COMPLETE)
			{
				GRG_CORE_ERROR("FrameBuffer not initialized: {}", status);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}


		void FrameBuffer::Resize(natural_t width, natural_t height)
		{
			Destroy(); //destroy frame buffer and the attached texture
			Create(); //create a new frame buffer
			Initialize(width, height);
		}
	} //namespace Renderer
} //namespace Gargantua