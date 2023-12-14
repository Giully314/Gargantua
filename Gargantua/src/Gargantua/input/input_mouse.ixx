/*
* gargantua/input/input_mouse.ixx
* 
* PURPOSE: Mouse functionalities.
* 
* CLASSES:
*	Mouse: Manage all the mouse related functionalities and info.
*/

export module gargantua.input.mouse;

import <array>;
import <algorithm>;

import gargantua.types;
import gargantua.math.vec2d;
import gargantua.input.mouse_codes;

namespace gargantua::input
{
	export class Mouse
	{
	public:
		constexpr explicit Mouse()
		{
			std::fill(buttons.begin(), buttons.end(), false);
		}


		auto SetPosition(const f32 x, const f32 y) noexcept -> void
		{
			position.x = x;
			position.y = y;
		}

		auto GetPosition() const noexcept -> const math::Vec2df&
		{
			return position;
		}


		auto SetButton(MouseButton b, bool state) -> void
		{
			buttons[+b] = state;
		}

		auto GetButton(MouseButton b) const -> bool
		{
			return buttons[+b];
		}


	private:
		math::Vec2df position;
		std::array<bool, static_cast<size_t>(MouseButton::NumOfButtons)> buttons;
	};
} // namespace gargantua::input