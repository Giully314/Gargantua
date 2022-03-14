#pragma once
/*
Gargantua/Renderer/Buffer.hpp

PURPOSE: Wrapper class for OpenGL Buffer object.


CLASSES:
	Buffer: Base class for Vertex buffer and Element buffer.


DESCRIPTION:
	This class is intented to be a wrapper and NOT an abstraction of OpenGL.
	This means that all the operations will be explicit and that the RAII is not implemented.


NOTEs FOR FUTURE CHANGES:
I can make the function Load in the interface of Buffer with this signature:
virtual void Load(const void* data, size_t num_bytes, DrawMode mode, natural_t element_size) = 0;
In case of the ElementBuffer, with element_size i can retrieve the count of indices.

*/

#include <glad/glad.h>
#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/Types.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		struct BufferInfo
		{
			BufferElementType type = BufferElementType::float_t;
			natural_t count = 0;
			natural_t elem_per_vert = 0; //element per vertex in VertexBuffer, 0 for ElementBuffer.
			DrawMode draw_mode = DrawMode::static_draw;
		};


		class Buffer : private NonCopyable
		{
		public:
			Buffer() = default;

			Buffer(Buffer&&) = default;
			Buffer& operator=(Buffer&&) = default;

			virtual ~Buffer();

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			inline void Create()
			{
				glGenBuffers(1, &id);
			}

			inline void Destroy()
			{
				glDeleteBuffers(1, &id);
				id = 0;
			}


			const BufferInfo& GetInfo() const noexcept 
			{
				return info;
			}

		protected:
			GLuint id = 0;
			BufferInfo info;
		};
	} //namespace Renderer
} //namespace Gargantua