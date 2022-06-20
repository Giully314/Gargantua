#pragma once
/*
Gargantua/Renderer/ElementBuffer.hpp

PURPOSE: Wrapper class for OpenGL ElementBuffer object.


CLASSES:
	ElementBufferInfo: info for the buffer.
	ElementBuffer: Class for ElementBuffer object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A buffer is just an array of data. 
	For now the element buffer loads only unsigned short indices.
*/

#include "Gargantua/Renderer/Types.hpp"
#include "Gargantua/Renderer/OpenGLObject.hpp"

#include "Gargantua/Types.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		struct ElementBufferInfo
		{
			natural_t count = 0;
			DrawMode draw_mode = DrawMode::static_draw;
		};


		class ElementBuffer : public OpenGLObject
		{
		public:

			void Create()
			{
				glGenBuffers(1, &id);
			}

			void Destroy()
			{
				glDeleteBuffers(1, &id);
				id = 0;
			}


			void Bind() const 
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			}

			void Unbind() const 
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			

			natural_t GetCount() const noexcept
			{
				return info.count;
			}

			const ElementBufferInfo& GetInfo() const noexcept
			{
				return info;
			}


			void Load(const void* data, natural_t count,  DrawMode mode);


		private:
			ElementBufferInfo info;
		};

	} //namespace Renderer
} //namespace Gargantua