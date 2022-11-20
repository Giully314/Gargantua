/*
gargantua/render/opengl_object.ixx

PURPOSE: Base class of every OpenGL object.

CLASSES:
	OpenGLObject: common info for every OpenGL object.


DESCRIPTION:
	Every OpenGL object has an id. This class is used as base class to avoid the repetition of this information
	and to provide a function to access the id.
*/
export module gargantua.render.opengl_object;

import gargantua.types;


namespace gargantua::render
{
	export class OpenGLObject
	{
	public:
		OpenGLObject() = default;
		
		OpenGLObject(OpenGLObject&&) = default;
		OpenGLObject& operator=(OpenGLObject&&) = default;

		OpenGLObject(const OpenGLObject&) = delete;
		OpenGLObject& operator=(const OpenGLObject&) = delete;


		auto GetRenderId() const noexcept -> render_id_t
		{
			return id;
		}

	protected:
		render_id_t id = 0;
	}; //class OpenGLObject
} //namespace gargantua::render
