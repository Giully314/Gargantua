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


			bool GetButton(mouse_t button) const { return buttons[button]; }
			void SetButton(mouse_t button, bool value) { buttons[button] = value; }

			real_t GetX() const noexcept { return x; }
			real_t GetY() const noexcept { return y; }

			void SetX(real_t x) { this->x = x; }
			void SetY(real_t y) { this->y = y; }

			void SetCoords(real_t x, real_t y)
			{
				this->x = x;
				this->y = y;
			}


			void ResetState()
			{
				x = 0.0f;
				y = 0.0f;
				buttons.fill(false);
			}


		private:
			real_t x;
			real_t y;
			std::array<bool, Mouse::NUM_OF_BUTTONS> buttons;
		};
	} //namespace Input 
} //namespace Gargantua


