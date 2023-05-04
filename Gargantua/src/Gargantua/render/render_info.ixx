/*
* gargantua/render/render_info.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* 
*/

module;

#include <glad/glad.h>

export module gargantua.render.render_info;


namespace gargantua::render
{
	export
	enum class BufferDraw
	{
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
	};

} // namespace gargantua::render
