/*
* gargantua/render/base_buffer.ixx
*
* PURPOSE: Abstraction for the opengl buffers.
*
* CLASSES:
*	BaseBuffer: Basic class to handle common operations of buffers (VBO and EBO).
*
* DESCRIPTION:
*	This class implements the Create and Destroy methods, common to buffers. 
* 
* TODO:
*	- Consider to use glNamedBufferStorage for the creation of the immutable buffer.
*	- Add an enum class to specify the draw mode (static, dynamic and so on).
*/

module;

#include <glad/glad.h>

export module gargantua.render.buffer:base_buffer;

import <utility>;

import gargantua.types;
import gargantua.render.opengl_object;
import gargantua.render.render_info;

namespace gargantua::render
{
	export
	class BaseBuffer : public OpenGLObject
	{
	public:

		// Precondition: an opengl context must exist.
		BaseBuffer()
		{
			glCreateBuffers(1, &id);
		}

		BaseBuffer(BaseBuffer&& other) noexcept  : OpenGLObject(other.id)
		{
			other.id = 0;
		}
		
		[[nodiscard]]
		auto operator=(BaseBuffer&& other) noexcept -> BaseBuffer&
		{
			if (&other != this)
			{
				Destroy();
				std::swap(id, other.id);
			}
			return *this;
		}

		~BaseBuffer()
		{
			Destroy();
		}


		auto Destroy() -> void
		{
			glDeleteBuffers(1, &id);
			id = 0;
		}


		auto GetDrawMode() const noexcept -> BufferDraw
		{
			return draw_mode;
		}

	protected:
		auto Load(const void* data, u64 num_of_bytes, BufferDraw draw) -> void
		{
			draw_mode = draw;
			glNamedBufferData(id, num_of_bytes, data, static_cast<GLenum>(draw_mode));
		}


		auto LoadSubData(const void* data, u64 num_of_bytes) -> void
		{
			glNamedBufferSubData(id, 0, num_of_bytes, data);
		}

	protected:
		BufferDraw draw_mode;
	};
} // namespace gargantua::render
