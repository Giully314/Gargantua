#pragma once
/*
Gargantua/Renderer/ElementBuffer.hpp

PURPOSE: Wrapper class for OpenGL ElementBuffer object.


CLASSES:
	ElementBuffer: Class for ElementBuffer object.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.
	A buffer is just an array of data. The meaning of this data is given by the VertexArray
	and the geometry associated (points, line, triangles and so on).
*/

#include "Gargantua/Renderer/Buffer.hpp"
#include "Gargantua/Renderer/Types.hpp"

#include "Gargantua/Types.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		class ElementBuffer : public Buffer
		{
		public:
			inline void Bind() const override
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			}

			inline void Unbind() const override
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			
			void Load(const void* data, natural_t count, BufferElementType type, DrawMode mode);


			inline natural_t GetCount() const noexcept
			{
				return info.count;
			}
		};

	} //namespace Renderer
} //namespace Gargantua