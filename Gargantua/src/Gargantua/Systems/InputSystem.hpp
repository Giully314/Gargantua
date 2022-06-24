#pragma once
/*
Gargantua/Core/InputSystems.hpp

PURPOSE: Handle the inputs.

CLASSES:
	InputSystem: Keep the state of keyboard and mouse.


DESCRIPTION:
	This class keeps the state of inputs using events of GLFW. The state is "locked" at the 
	start of every frame;
	this means that events of the engine are processed at the start of the game loop and the 
	state of the input is updated and ready to be used for the current frame.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Input/KeyboardState.hpp"
#include "Gargantua/Input/MouseState.hpp"

#include "Gargantua/Event/EventListenerManager.hpp"

#include "Gargantua/Systems/EventSystem.hpp"

#include "Gargantua/Math/Vec2d.hpp"


namespace Gargantua
{
	namespace Systems
	{
		class InputSystem
		{
		public:
			InputSystem();

			void ListenAndRegisterEvents(SharedRes<Systems::EventSystem> event_sys);
			
			static bool IsPressed(key_t key) noexcept
			{
				return keyboard->GetKey(key);
			}

			static Math::Vec2df MouseCoords() noexcept
			{
				return Math::Vec2df{ mouse->GetX(), mouse->GetY() };
			}


			static void ResetState()
			{
				keyboard->ResetState();
				mouse->ResetState();
			}
			

		private:
			static UniqueRes<Input::KeyboardState> keyboard;
			static UniqueRes<Input::MouseState> mouse;
		};
	} //namespace Systems
} //namespace Gargantua