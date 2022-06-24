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
		void OrthoCameraController::Update(const Time::TimeStep& ts)
		{
			const real_t time = (real_t)ts.GetInSec();

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