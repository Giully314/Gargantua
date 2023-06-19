/*
* gargantua/render/camera.cpp
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.render.camera;

import <algorithm>;

import gargantua.platform.platform;
import gargantua.log.log;

namespace gargantua::render
{
	auto Camera::Startup() -> void
	{
		using namespace platform;
		auto& ev = PlatformEventDispatcher::Instance();

		ev.RegisterListener<MouseWheelScrollEvent>([&](const MouseWheelScrollEvent& e)
			{
				GRG_CORE_DEBUG("Calling MouseWheelScroll listener with {}", e.y_offset);
				distance -= e.y_offset * 0.1f; // *ZoomSpeed();
				distance = std::max(distance, 1.0f);
				GRG_CORE_DEBUG("Camera distance {}", distance);
				GRG_CORE_DEBUG("Projection\n{}", projection.ToString());
				ComputeProjection();
			});
	}
	

	auto Camera::ZoomSpeed() const -> f32
	{
		f32 d = distance * 0.1f;
		d = std::min(d, 0.0f);
		return std::min(30.0f, d * d);
	}


	auto Camera::ComputeProjection() -> void
	{
		// Note that if we want 0 center, we must pass -width/2, -height/2, width/2, height/2
		//auto half_width = viewport_width / 2.0f;
		//auto half_height = viewport_height / 2.0f;
		f32 aspect_ratio = static_cast<f32>(viewport_width) / static_cast<f32>(viewport_height);
		projection = math::Projection::Orthographic(-aspect_ratio * distance, -distance, aspect_ratio * distance,
			distance, -1.0f, 1.0f);
	}
} // namespace gargantua::render
