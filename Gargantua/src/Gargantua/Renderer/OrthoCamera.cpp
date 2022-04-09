/*
Gargantua/Renderer/OrthoCamera.cpp
*/

#include "OrthoCamera.hpp"

#include "Gargantua/Math/Functions.hpp"


namespace Gargantua
{
	namespace Renderer
	{
		OrthoCamera::OrthoCamera(real_t l, real_t b, real_t r, real_t t, real_t n, real_t f) : position(), rotation(0.0f),
			projection(Math::Projection::Orthographic(l, b, r, t, n, f)),
			view(1.0f), proj_view()
		{
			UpdateCameraMatrix();
			//proj_view = projection * view;
		}

		OrthoCamera::OrthoCamera(real_t l, real_t b, real_t r, real_t t) : position(), rotation(0.0f),
			projection(Math::Projection::Orthographic(l, b, r, t)),
			view(1.0f), proj_view()
		{
			proj_view = projection * view;
		}


		void OrthoCamera::UpdateCameraMatrix()
		{
			Math::Mat4df transform = Math::Transform3d::Translate(position) * Math::Transform3d::RotateZ((real_t)Math::Angles::ToRad(rotation));
			view = transform.Inverse();

			proj_view = projection * view;
		}
	} // namespace Renderer
} // namespace Gargantua
