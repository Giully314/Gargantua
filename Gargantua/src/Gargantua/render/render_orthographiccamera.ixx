/*
* gargantua/render/render_orthographiccamera.ixx
* 
* PURPOSE: Provide an orthographic camera for testing.
* 
* CLASSES:
*	OrthoCamera: Class used for tests.
* 
*/

export module gargantua.render.orthographic_camera;

import gargantua.types;
import gargantua.math.vector;
import gargantua.math.matrix;
import gargantua.math.functions;


namespace gargantua::render
{
	export class OrthoCamera
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

		auto SetPosition(const math::Vec3df& position) -> void
		{
			this->position = position;
			ComputeViewProjection();
		}

		auto SetPositionRotation(const math::Vec3df& position, f32 rotation)
		{
			this->position = position;
			this->rotation = rotation;
			ComputeViewProjection();
		}

		auto GetPosition() const noexcept -> const math::Vec3df&
		{
			return position;
		}

		auto GetRotation() const noexcept -> f32
		{
			return rotation;
		}


		auto SetProjection(f32 l, f32 b, f32 r, f32 t) -> void
		{
			projection = math::Projection::Orthographic(l, b, r, t, -1.0f, 1.0f);
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
