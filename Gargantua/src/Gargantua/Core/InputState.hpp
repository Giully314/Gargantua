#pragma once

#include "Gargantua/Types.hpp"

#include "Gargantua/Input/KeyboardState.hpp"
#include "Gargantua/Input/MouseState.hpp"

#include "Gargantua/Event/EventListenerSystem.hpp"


namespace Gargantua
{
	namespace Core
	{
		class InputState
		{
		public:
			InputState();

			void ListenToEvents(NonOwnedRes<Event::EventListenerSystem>);
			
			inline static bool IsPressed(key_t key) noexcept
			{
				return keyboard->GetKey(key);
			}

			inline static void MouseCoords() noexcept
			{
				
			}

		private:
			static UniqueRes<Input::KeyboardState> keyboard;
			static UniqueRes<Input::MouseState> mouse;
			
			void Init();
		};
	} //namespace Input
} //namespace Gargantua