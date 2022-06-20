#pragma once
/*
Gargantua/Renderer/OpenGLObject.hpp

PURPOSE: Base class of every OpenGL object.

CLASSES:
	OpenGLObject: common info for every OpenGL object.


DESCRIPTION:
	Every OpenGL object has an id. This class is used as base class to avoid the repetition of this information
	and to provide a function to access the id.
*/


#include <glad/glad.h>

#include "Gargantua/Types.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		class OpenGLObject : private NonCopyable
		{
		public:
			/*OpenGLObject() = default;
			OpenGLObject(OpenGLObject&&) = default;
			OpenGLObject& operator=(OpenGLObject&&) = default;*/

			render_id_t GetRenderId() const noexcept
			{
				return id;
			}

		protected:
			render_id_t id = 0;
		};

	} //namespace Renderer
} //namespace Gargantua
