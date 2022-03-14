#pragma once
/*
Gargantua/Renderer/VertexBuffer.hpp

PURPOSE: Wrapper class for OpenGL VertexBuffer object.


CLASSES:
	VertexBuffer: Class for VertexBuffer object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A buffer is just an array of data. The meaning of this data is given by the VertexArray
	and the geometry associated (points, line, triangles and so on).
	For now the vertex buffer allows to load only floating point data.


USAGE:
	
*/


#include <glad/glad.h>

#include "Gargantua/Renderer/Buffer.hpp"
#include "Gargantua/Renderer/Types.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		class VertexBuffer : public Buffer
		{
		public:
			inline void Bind() const override
			{
				glBindBuffer(GL_ARRAY_BUFFER, id);
			}

			inline void Unbind() const override
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			
			/*
			The buffer is unbinded after the load of the data.
			*/
			void Load(const void* data, natural_t count, natural_t elem_per_vert, BufferElementType type, DrawMode mode);
		};
	} //namespace Renderer
} //namespace Gargantua