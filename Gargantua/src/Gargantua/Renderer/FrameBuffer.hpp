#pragma once
/*
Gargantua/Renderer/FrameBuffer.hpp

PURPOSE:

CLASSES:

DESCRIPTION:


TODO:
	I don't like the way i manage the buffer inside Create and Destroy();

*/

#include <glad/glad.h>

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/OpenGLObject.hpp"
#include "Gargantua/Renderer/Texture2d.hpp"


namespace Gargantua
{
	namespace Renderer
	{
		class FrameBuffer : public OpenGLObject
		{
		public:
			void Create()
			{
				glGenFramebuffers(1, &id);
			}

			void Destroy()
			{
				glDeleteFramebuffers(1, &id);
				id = 0;
				buffer.Destroy();
			}


			void Bind() const
			{
				glBindFramebuffer(GL_FRAMEBUFFER, id);
			}

			void Unbind() const
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}


			void Initialize(natural_t width, natural_t height);

			void Resize(natural_t width, natural_t height);


			Texture2d& GetColorBuffer() 
			{
				return buffer;
			}


			render_id_t GetColorBufferId() const
			{
				return buffer.GetRenderId();
			}


			natural_t GetHeight() const noexcept 
			{
				return buffer.GetHeight();
			}

			natural_t GetWidth() const noexcept
			{
				return buffer.GetWidth();
			}

		private:
			Texture2d buffer;
		};
	} //namespace Renderer
} //namespace Gargantua