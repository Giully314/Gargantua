/*
* gargantua/render/camera.ixx
* 
* PURPOSE: Camera projection used in game.
* TODO:
*	This is a test file and it will probably be moved to another location.
*/

export module gargantua.render.camera;

import gargantua.types;
import gargantua.math;

namespace gargantua::render
{
	export
	class Camera
	{
	public:
		// Register to events for mouse wheel and framebuffer resize (if enabled).
		auto Startup() -> void;

		auto GetProjection() const noexcept -> const math::Mat4df&
		{
			return projection;
		}

		auto SetViewport(u32 width, u32 height) -> void 
		{
			viewport_width = width;
			viewport_height = height;
			ComputeProjection();
		}

		auto GetDistance() const -> f32
		{
			return distance;
		}

	private:
		// Compute the zoom speed based on the current distance.
		auto ZoomSpeed() const->f32;

		auto ComputeProjection() -> void;

	private:
		math::Mat4df projection{ 1.0f };
		f32 distance = 5.0f; // used with mouse wheel
		u32 viewport_width;
		u32 viewport_height;
	};
} // namespace gargantua::render
