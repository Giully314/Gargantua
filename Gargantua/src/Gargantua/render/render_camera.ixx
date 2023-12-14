/*
* gargantua/render/render_camera.ixx
* 
* PURPOSE: Provide the basic camera functionality.
* 
* CLASSES:
*	Camera: 
* 
* DESCRIPTION:
*	 
*/

export module gargantua.render.camera;

import gargantua.types;
import gargantua.math;
import gargantua.event;
import gargantua.input;

namespace gargantua::render
{
	export class Camera
	{
	public:
		constexpr explicit Camera() = default;

		// Register to events for mouse wheel and framebuffer resize (if enabled).
		auto Startup() -> void
		{
			using namespace event;
			using namespace input;
			auto& ev = EngineEventDispatcher();

			// TODO: this is temporary. This should be settable by the user and not hardcoded.
			ev.RegisterListener<MouseWheelScrollEvent>([&](const BaseEvent& e)
				{
					const auto& me = static_cast<const MouseWheelScrollEvent&>(e);
					//GRG_CORE_DEBUG("Calling MouseWheelScroll listener with {}", e.y_offset);
					distance -= me.y_offset * 0.1f; // *ZoomSpeed();
					distance = std::max(distance, 1.0f);
					/*GRG_CORE_DEBUG("Camera distance {}", distance);
					GRG_CORE_DEBUG("Projection\n{}", projection.ToString());*/
					ComputeProjection();
				});
		}

		constexpr auto Projection() const noexcept -> const math::Mat4df&
		{
			return projection;
		}

		constexpr auto SetViewport(const u32 width, const u32 height) -> void 
		{
			viewport_width = width;
			viewport_height = height;
			ComputeProjection();
		}

		constexpr auto Distance() const noexcept -> f32
		{
			return distance;
		}

	private:
		// Compute the zoom speed based on the current distance.
		constexpr auto ZoomSpeed() const -> f32
		{
			f32 d = distance * 0.1f;
			d = std::min(d, 0.0f);
			return std::min(30.0f, d * d);
		}

		constexpr auto ComputeProjection() -> void
		{
			// Note that if we want 0 center, we must pass -width/2, -height/2, width/2, height/2
			//auto half_width = viewport_width / 2.0f;
			//auto half_height = viewport_height / 2.0f;
			f32 aspect_ratio = static_cast<f32>(viewport_width) / static_cast<f32>(viewport_height);
			projection = math::Projection::Orthographic(-aspect_ratio * distance, -distance, aspect_ratio * distance,
				distance, -1.0f, 1.0f);
		}

	private:
		math::Mat4df projection{ 1.0f };
		f32 distance = 5.0f; // used with mouse wheel
		u32 viewport_width;
		u32 viewport_height;
	};
} // namespace gargantua::render
