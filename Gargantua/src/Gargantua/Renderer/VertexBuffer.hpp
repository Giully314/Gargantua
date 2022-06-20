#pragma once
/*
Gargantua/Renderer/VertexBuffer.hpp

PURPOSE: Wrapper class for OpenGL VertexBuffer object.


CLASSES:
	VertexBufferInfo: info for the buffer.
	VertexBuffer: Class for VertexBuffer object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A buffer is just an array of data. 
	For now the vertex buffer allows to load only floating point data.


USAGE:
	VertexBuffer vb;
	vb.Create();
	vb.Load(...);

	...

	vb.Destroy();
*/


#include <glad/glad.h>

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/OpenGLObject.hpp"
#include "Gargantua/Renderer/Types.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		struct VertexBufferInfo
		{
			natural_t elem_per_vert = 0; 
			DrawMode draw_mode = DrawMode::static_draw;
		};


		class VertexBuffer : public OpenGLObject
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
				glBindBuffer(GL_ARRAY_BUFFER, id);
			}

			void Unbind() const 
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}


			const VertexBufferInfo& GetInfo() const noexcept 
			{
				return info;
			}

			
			/*
			The buffer is unbinded after the load of the data.
			*/
			void Load(const void* data, natural_t count, natural_t elem_per_vert, DrawMode mode);
		

		private:
			VertexBufferInfo info;
		};
	} //namespace Renderer
} //namespace Gargantua