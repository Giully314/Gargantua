/*
* gargantua/render/render_info.ixx
* 
* PURPOSE: provide info about the rendering components.
* 
* CLASSES:
*	BufferDraw: specify if a buffer is static or dynamic.
*/

module;

#include <glad/glad.h>

export module gargantua.render.render_info;


namespace gargantua::render
{
	export enum class BufferDraw
	{
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
	};

} // namespace gargantua::render
