/*
* gargantua/render/opengl_object.ixx
* 
* PURPOSE: Basic opengl info.
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
	export
	class OpenGLObject : private NonCopyable
	{
	public:
		OpenGLObject() = default;
		
		// can't be defaulted because noncopyable
		auto operator==(const OpenGLObject& other) const -> bool
		{
			return id == other.id;
		}

		auto GetID() const noexcept -> render_id_t
		{
			return id;
		}

	protected:
		OpenGLObject(render_id_t id_) : id(id_)
		{

		}

	protected:
		render_id_t id = 0;
	};
} // namespace gargantua::render
