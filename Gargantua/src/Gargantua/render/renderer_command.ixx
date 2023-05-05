/*
* gargantua/render/renderer_command.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* 
* TODO:
*	- for now it is only 2d oriented, update for 3d when supported.
*	- line width.
*/

module;

#include <glad/glad.h>

export module gargantua.render.renderer_command;

import gargantua.render.vertex_array;
import gargantua.math.vector;


namespace gargantua::render
{
	// Precondition: an opengl context must exist.
	export
	struct RendererCommand
	{
		static auto SetClearColor(math::Vec4df color) -> void
		{
			glClearColor(color.x, color.y, color.z, color.w);
		}

		static auto EnableBlending() -> void
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		static auto Clear() -> void
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}

		static auto SetViewport(u32 x, u32 y, u32 width, u32 height) -> void
		{
			glViewport(x, y, width, height);
		}

		static auto DrawIndexed(const VertexArray& vao) -> void
		{
			vao.Bind();
			glDrawElements(GL_TRIANGLES, vao.GetCount(), GL_UNSIGNED_INT, 0);
		}

		static auto DrawIndexed(const VertexArray& vao, u32 count) -> void 
		{
			vao.Bind();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
		}

		static auto DrawArray(const VertexArray& vao, u32 count) -> void
		{
			vao.Bind();
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	};
} // namespace gargantua::render
