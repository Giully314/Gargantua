/*
* gargantua/platform/keyboard.ixx
* 
* PURPOSE: Manage keyboard.
* CLASSES:
*	Keyboard: Manage all the functionalities and info about the keyboard.
*/

export module gargantua.platform.keyboard;


import <array>;
import <algorithm>;

import gargantua.types;
import gargantua.platform.key_codes;


export namespace gargantua::platform
{
	class Keyboard
	{
	public:
		Keyboard()
		{
			std::fill(keyboard_state.begin(), keyboard_state.end(), false);
		}

		auto SetKey(Key k, bool state) -> void
		{
			keyboard_state[+k] = state;
		}

		auto IsPressed(Key k) const -> bool
		{
			return keyboard_state[+k];
		}

	private:
		std::array<bool, static_cast<size_t>(Key::NUM_OF_KEYS)> keyboard_state;
	};
} // namespace gargantua::platform