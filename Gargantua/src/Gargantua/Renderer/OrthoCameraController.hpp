#pragma once
/*
Gargantua/Renderer/OrthoCameraController.hpp

PURPOSE: OrthoCamera controller for debug purpose.

CLASSES:
	OrthoCameraController: Controller for the camera.


DESCRIPTION:
	Note: this class is intented to be used only for debug purpose and testing the engine 
	and not for game camera.

*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/OrthoCamera.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Math/Vec3d.hpp"


#include <utility>

namespace Gargantua
{
	namespace Renderer
	{
		class OrthoCameraController
		{
		public:
			OrthoCameraController() = default;


			void Update(const Time::TimeStep& ts);


			void SetCamera(SharedRes<OrthoCamera> camera)
			{
				this->camera = camera;
			}


			OrthoCamera& GetCamera() const noexcept
			{
				return *camera;
			}


			void CreateCamera(real_t aspect_ratio)
			{
				this->aspect_ratio = aspect_ratio;
				camera = CreateSharedRes<OrthoCamera>(-aspect_ratio * zoom_level, 
					-zoom_level, aspect_ratio * zoom_level, zoom_level);
			}

			void ZoomLevelOffset(real_t offset)
			{
				zoom_level -= offset * 0.25f;
				zoom_level = std::max(zoom_level, 0.5f);

				camera->SetProjection(-aspect_ratio * zoom_level,
					-zoom_level, aspect_ratio * zoom_level, zoom_level);
			}
		

		private:
			SharedRes<OrthoCamera> camera = nullptr;

			Math::Vec3df position;
			real_t rotation = 0.0f;

			real_t velocity = 1.0f;
			real_t angular_velocity = 50;

			real_t zoom_level = 5.0f;

			real_t aspect_ratio = 0.0f;
		};
	} //namespace Renderer
} //namespace Gargantua