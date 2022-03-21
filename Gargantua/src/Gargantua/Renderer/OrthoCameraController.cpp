/*
Gargantua/Renderer/OrthoCameraController.cpp
*/

#include "OrthoCameraController.hpp"


#include "Gargantua/Systems/InputSystem.hpp"
#include "Gargantua/Input/KeyCodes.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		
		OrthoCameraController::OrthoCameraController(NonOwnedRes<OrthoCamera> camera_) : camera(camera_),
			position(), rotation(0.0f), velocity(0.1f), angular_velocity(0.1f)
		{

		}


		void OrthoCameraController::Update(const Time::TimeStep& ts)
		{
			const real_t time = ts.GetInSec();

			if (Systems::InputSystem::IsPressed(Input::Key::W))
			{
				position.y += velocity * time;
			}
			if (Systems::InputSystem::IsPressed(Input::Key::S))
			{
				position.y -= velocity * time;
			}
			if (Systems::InputSystem::IsPressed(Input::Key::D))
			{
				position.x += velocity * time;
			}
			if (Systems::InputSystem::IsPressed(Input::Key::A))
			{
				position.x -= velocity * time;
			}
			if (Systems::InputSystem::IsPressed(Input::Key::RIGHT))
			{
				rotation -= angular_velocity * time;
			}
			else if (Systems::InputSystem::IsPressed(Input::Key::LEFT))
			{
				rotation += angular_velocity * time;
			}
			
			camera->SetPositionAndRotation(position, rotation);
		}
	} //namespace Renderer
} //namespace Gargantua