/*
gargantua/input/keyboard_state.ixx

PURPOSE: State of the keyboard.

CLASSES:
	KeyboardState: Manages the state of the keyboard.

DESCRIPTION:
	Simple class that mainstains the state of the keyboard in the current frame using a std::array.

USAGE:
	keyboard_state.GetKey(Input::Key::ARROW_UP);

TODO: maintains previous state?

*/

export module gargantua.input.keyboard:keyboard_state;

import <array>;

import :key_codes;
import gargantua.types;



namespace gargantua::input
{

	/*
	Simple class that mainstains the state of the keyboard in the current frame.
	TODO: maintains previous state?
	*/
	export class KeyboardState
	{
	public:
		KeyboardState()
		{
			keyboard.fill(false);
		}


		auto ResetState() -> void
		{
			keyboard.fill(false);
		}


		auto SetKey(key_t key, bool value) -> void
		{
			keyboard[key] = value;
		}


		auto GetKey(key_t key) const -> bool
		{
			return keyboard[key];
		}


	private:
		std::array<bool, key::NUM_OF_KEYS> keyboard;
	}; //class KeyboardState
} //namespace gargantua::input


