/*
* gargantua/render/orthographic_camera.ixx
* 
* TEMPORARY FILE FOR TESTING.
*/

export module gargantua.render.orthographic_camera;

import gargantua.types;
import gargantua.math.vector;
import gargantua.math.matrix;
import gargantua.math.math_functions;


namespace gargantua::render
{
	export 
	class OrthoCamera
	{
	public:
		OrthoCamera(f32 l, f32 b, f32 r, f32 t)
		{
			projection = math::Projection::Orthographic(l, b, r, t, -1.0f, 1.0f);
			view.Identity();
			view_projection = projection * view;
		}

		auto SetRotation(f32 rotation) -> void
		{
			this->rotation = rotation;
			ComputeViewProjection();
		}

		auto SetPosition(math::Vec3df position) -> void
		{
			this->position = position;
			ComputeViewProjection();
		}


		auto GetViewProjection() const noexcept -> const math::Mat4df&
		{
			return view_projection;
		}

		// This is like the update method.
		auto ComputeViewProjection() -> void
		{
			ComputeView();
			view_projection = projection * view;
		}

	private:
		auto ComputeView() -> void
		{
			auto transform = math::Transform3d::Translate(position) * math::Transform3d::RotateZ(rotation);
			view = transform.Inverse();
		}


	private:
		math::Vec3df position;
		f32 rotation = 0.0f;
		math::Mat4df projection;
		math::Mat4df view;
		math::Mat4df view_projection; // first view then projection
	};
} // namespace gargantua::render
