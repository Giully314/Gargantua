/*
gargantua/render/renderer_command.ixx


PURPOSE: Rendering instructions.

CLASSES:
	RendererCommand: struct with static methods for rendering instructions.


DESCRIPTION:
	This set of functions is used to "instruct" the underlying renderer library (in this case OpenGL).
	Draw calls, set various parameters, blending, ecc.
*/

module;

#include <glad/glad.h>

export module gargantua.render.renderer_command;

import gargantua.types;

import gargantua.render.render_types;
import gargantua.render.element_buffer;

import gargantua.math.vec4d;


namespace gargantua::render
{

	export struct RendererCommand
	{
		static auto SetClearColor(const math::Vec4df& color) -> void
		{
			glClearColor(color[0], color[1], color[2], color[3]);
		}

		static auto Clear() -> void
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}


		static auto SetViewport(natural_t x, natural_t y, natural_t width, natural_t height) -> void
		{
			glViewport(x, y, width, height);
		}


		static auto EnableBlending() -> void
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}


		static auto Draw(const ElementBuffer& eb) -> void
		{
			glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_SHORT, nullptr);
		}
	}; //struct RendererCommand

} //namespace gargantua::render