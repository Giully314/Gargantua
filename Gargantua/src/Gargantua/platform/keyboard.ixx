/*
* gargantua/platform/keyboard.ixx
* 
* PURPOSE:
* CLASSES:
* DESCRIPTION:
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
			//std::ranges::fill(keyboard_state, false); doesn't work, why? 
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