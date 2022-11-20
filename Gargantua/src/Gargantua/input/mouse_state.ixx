/*
gargantua/input/mouse_state.ixx

PURPOSE: Keep the state of the mouse.

CLASSES:
	MouseState: Information about the state of the mouse.

DESCRIPTION:
	State of the mouse in the current frame. Position and buttons pressed.

USAGE:
	mouse_state.GetX();

*/

export module gargantua.input.mouse:mouse_state;

import <array>;

import :mouse_codes;
import gargantua.types;


namespace gargantua::input
{

	export class MouseState
	{
	public:
		MouseState() : x(0.0f), y(0.0f)
		{
			buttons.fill(false);
		}


		auto GetButton(mouse_t button) const -> bool 
		{ 
			return buttons[button]; 
		}


		auto SetButton(mouse_t button, bool value) -> void 
		{ 
			buttons[button] = value; 
		}


		auto GetX() const noexcept -> real_t 
		{ 
			return x; 
		}

		auto GetY() const noexcept -> real_t 
		{ 
			return y; 
		}


		auto SetX(real_t x) -> void 
		{ 
			this->x = x; 
		}


		auto SetY(real_t y) -> void 
		{ 
			this->y = y; 
		}

		auto SetCoords(real_t x, real_t y) -> void
		{
			this->x = x;
			this->y = y;
		}


		auto ResetState() -> void
		{
			x = 0.0f;
			y = 0.0f;
			buttons.fill(false);
		}


	private:
		real_t x;
		real_t y;
		std::array<bool, mouse::NUM_OF_BUTTONS> buttons;
	}; //class MouseState
} //namespace gargantua::input


