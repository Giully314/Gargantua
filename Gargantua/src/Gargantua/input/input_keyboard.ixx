/*
* gargantua/input/input_keyboard.ixx
* 
* PURPOSE: Manage keyboard.
* CLASSES:
*	Keyboard: Manage all the functionalities and info about the keyboard.
*/

export module gargantua.input.keyboard;

import <array>;
import <algorithm>;

import gargantua.types;
import gargantua.input.key_codes;


namespace gargantua::input
{
	export class Keyboard
	{
	public:
		constexpr explicit Keyboard()
		{
			std::fill(keyboard_state.begin(), keyboard_state.end(), false);
		}

		auto SetKey(const Key k, const bool state) noexcept -> void
		{
			keyboard_state[+k] = state;
		}

		auto IsPressed(const Key k) const noexcept -> bool
		{
			return keyboard_state[+k];
		}

	private:
		std::array<bool, static_cast<size_t>(Key::NumOfKeys)> keyboard_state;
	};
} // namespace gargantua::input