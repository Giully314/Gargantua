#pragma once

#include "Gargantua/Types.hpp"
#include "Gargantua/Input/MouseCodes.hpp"


#include <array>

namespace Gargantua
{
	namespace Input
	{
		//State of the mouse in the current frame.
		class MouseState
		{
		public:
			MouseState() : x(0), y(0)
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


