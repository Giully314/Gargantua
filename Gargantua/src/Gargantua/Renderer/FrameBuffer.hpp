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

#include "Gargantua/Renderer/Texture2d.hpp"

namespace Gargantua
{
	namespace Renderer
	{

		/*
		Temporary solution while deciding how to do it.
		The render buffer is only color because the engine is for 2d only.
		*/
		/*class RenderBuffer : private NonCopyable
		{
		public:
			friend class FrameBuffer;

			inline void Create(natural_t width, natural_t height)
			{
				glGenRenderbuffers(1, &id);
				glBindRenderbuffer(GL_RENDERBUFFER, id);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
			}


			inline void Destroy()
			{
				glDeleteRenderbuffers(1, &id);
				id = 0;
			}

			inline void Bind() const
			{
				glBindRenderbuffer(GL_RENDERBUFFER, id);
			}

			inline void Unbind() const 
			{
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
			}

		private:
			GLuint id = 0;
		};*/



		class FrameBuffer : private NonCopyable
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

		private:
			GLuint id = 0;
			Texture2d buffer;
		};
	} //namespace Renderer
} //namespace Gargantua