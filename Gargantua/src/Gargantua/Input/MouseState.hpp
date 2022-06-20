#pragma once
/*
Gargantua/Input/MouseState.hpp

PURPOSE: Keep the state of the mouse.

CLASSES:
	MouseState: Information about the state of the mouse.

DESCRIPTION:
	State of the mouse in the current frame. Position and buttons pressed.

USAGE:
	mouse_state.GetX();

*/

#include "Gargantua/Types.hpp"
#include "Gargantua/Input/MouseCodes.hpp"


#include <array>

namespace Gargantua
{
	namespace Input
	{
		class MouseState
		{
		public:
			MouseState() : x(0.0f), y(0.0f)
			{
				buttons.fill(false);
			}


			inline bool GetButton(mouse_t button) const { return buttons[button]; }
			inline void SetButton(mouse_t button, bool value) { buttons[button] = value; }

			inline real_t GetX() const noexcept { return x; }
			inline real_t GetY() const noexcept { return y; }

			inline void SetX(real_t x) { this->x = x; }
			inline void SetY(real_t y) { this->y = y; }

			inline void SetCoords(real_t x, real_t y)
			{
				this->x = x;
				this->y = y;
			}

		private:
			real_t x;
			real_t y;
			std::array<bool, Mouse::NUM_OF_BUTTONS> buttons;
		};
	} //namespace Input 
} //namespace Gargantua


