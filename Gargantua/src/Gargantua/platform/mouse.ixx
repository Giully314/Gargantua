/*
* gargantua/platform/mouse.ixx
*/

export module gargantua.platform.mouse;

import <array>;
import <algorithm>;

import gargantua.types;
import gargantua.math.vec2d;
import gargantua.platform.mouse_codes;

export namespace gargantua::platform
{
	class Mouse
	{
	public:
		Mouse()
		{
			std::fill(buttons.begin(), buttons.end(), false);
		}


		auto SetPosition(f32 x, f32 y) -> void
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
		std::array<bool, static_cast<size_t>(MouseButton::NUM_OF_BUTTONS)> buttons;
	};
} // namespace gargantua::platform