/*
* gargantua/render/render_renderercommand.ixx
* 
* PURPOSE: Provide implementation of opengl commands.
* 
* CLASSES:
*	RendererCommand: implementation of static functions to invoke an OpenGL command. 
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
	export struct RendererCommand
	{
		/*
		* Set what color to use for clearing the screen.
		*/
		static auto SetClearColor(const math::Vec4df& color) -> void
		{
			glClearColor(color.x, color.y, color.z, color.w);
		}

		/*
		* Enable blending.
		*/
		static auto EnableBlending() -> void
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		/*
		* Clear the screen.
		*/
		static auto Clear() -> void
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}

		/*
		* Set viewport.
		*/
		static auto SetViewport(const u32 x, const u32 y, const u32 width, const u32 height) -> void
		{
			glViewport(x, y, width, height);
		}

		/*
		* Draw the passed vertex array.
		*/
		static auto DrawIndexed(const VertexArray& vao) -> void
		{
			vao.Bind();
			glDrawElements(GL_TRIANGLES, vao.Count(), GL_UNSIGNED_INT, 0);
		}

		/*
		* Draw the passed vertex array using only count number of indices.
		*/
		static auto DrawIndexed(const VertexArray& vao, const u32 count) -> void 
		{
			vao.Bind();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
		}

		/*
		* 
		*/
		static auto DrawArray(const VertexArray& vao, const u32 count) -> void
		{
			vao.Bind();
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	};
} // namespace gargantua::render
