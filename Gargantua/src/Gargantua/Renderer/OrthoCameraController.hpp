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


namespace Gargantua
{
	namespace Renderer
	{
		class OrthoCameraController
		{
		public:
			OrthoCameraController() = default;
			OrthoCameraController(NonOwnedRes<OrthoCamera> camera_);


			void Update(const Time::TimeStep& ts);


			inline void SetCamera(NonOwnedRes<OrthoCamera> camera)
			{
				this->camera = camera;
			}

		private:
			NonOwnedRes<OrthoCamera> camera = nullptr;

			Math::Vec3df position;
			real_t rotation = 0.0f;

			real_t velocity = 0.5f;
			real_t angular_velocity = 50;
		};
	} //namespace Renderer
} //namespace Gargantua