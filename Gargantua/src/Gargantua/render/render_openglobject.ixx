/*
* gargantua/render/render_openglobject.ixx
* 
* PURPOSE: Provide a common interface for opengl objects.
* 
* CLASSES:
*	OpenGLObject: stores the id of an opengl object. 
* 
* DESCRIPTION:
*	All classes that abstract one or more functionality of opengl must inherit from this class.
*	Every opengl object has an id.
*/

module;

#include <glad/glad.h>

export module gargantua.render.opengl_object;

import gargantua.types;

namespace gargantua::render
{
	export class OpenGLObject //: private NonCopyable
	{
	public:
		constexpr explicit OpenGLObject() = default;
		
		constexpr auto operator==(const OpenGLObject& other) const noexcept -> bool = default;

		constexpr auto ID() const noexcept -> render_id_t
		{
			return id;
		}

	protected:
		constexpr explicit OpenGLObject(render_id_t id_) : id(id_)
		{

		}

	protected:
		render_id_t id = 0;
	};
} // namespace gargantua::render
