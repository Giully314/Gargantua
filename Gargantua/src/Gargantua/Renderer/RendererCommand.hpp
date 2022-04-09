#pragma once
/*
Gargantua/Renderer/RendererCommand.hpp


PURPOSE: Rendering instructions.

CLASSES:
	RendererCommand: struct with static methods for rendering instructions.


DESCRIPTION:
	This set of functions is used to "instruct" the underlying renderer library (in this case OpenGL).
	Draw calls, set various parameters, blending, ecc.
*/

#include <glad/glad.h>

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/Types.hpp"
#include "Gargantua/Renderer/VertexArray.hpp"
#include "Gargantua/Renderer/Texture2d.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/Program.hpp"


#include "Gargantua/Math/Vec4d.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		struct RendererCommand
		{
			static inline void SetClearColor(const Math::Vec4df& color)
			{
				glClearColor(color[0], color[1], color[2], color[3]);
			}

			static inline void Clear()
			{
				glClear(GL_COLOR_BUFFER_BIT);
			}


			static inline void SetViewport(natural_t x, natural_t y, natural_t width, natural_t height)
			{
				glViewport(x, y, width, height);
			}


			static inline void EnableBlending()
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}


			static inline void Draw(const ElementBuffer& eb, RenderTopology t)
			{
				glDrawElements((GLenum)(t), eb.GetCount(), eb.GetGLType(), nullptr);
			}
		};
	} //namespace Renderer
} //namespace Gargantua