#pragma once
/*
Gargantua/Input/KeyboardState.hpp

PURPOSE: State of the keyboard.

CLASSES:
	KeyboardState: Manages the state of the keyboard.

DESCRIPTION:
	Simple class that mainstains the state of the keyboard in the current frame using a std::array.

USAGE:
	keyboard_state.GetKey(Input::Key::ARROW_UP);

TODO: maintains previous state?

*/

#include "Gargantua/Input/KeyCodes.hpp"
#include "Gargantua/Types.hpp"

#include <array>


namespace Gargantua
{
	namespace Input
	{
		/*
		Simple class that mainstains the state of the keyboard in the current frame. 
		TODO: maintains previous state?
		*/
		class KeyboardState
		{
		public:
			KeyboardState()
			{
				keyboard.fill(false);
			}

			
			inline void ResetState() { keyboard.fill(false); }

			inline bool GetKey(key_t key) const { return keyboard[key]; }
			inline void SetKey(key_t key, bool value) { keyboard[key] = value; }
	

		private:
			std::array<bool, Key::NUM_OF_KEYS> keyboard;
		};
	} //namespace Input
} //namespace Gargantua


