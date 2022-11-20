/*
gargantua/input/mouse_codes.ixx

PURPOSE: Codes for buttons of the mouse.

CLASSES:

DESCRIPTION:

USAGE:

*/

export module gargantua.input.mouse:mouse_codes;

import gargantua.types;

namespace gargantua::input
{

	export namespace mouse
	{
		//From glfw3.h
		enum : mouse_t
		{
			BUTTON_1 = 0,
			BUTTON_2 = 1,
			BUTTON_3 = 2,
			BUTTON_4 = 3,
			BUTTON_5 = 4,
			BUTTON_6 = 5,
			BUTTON_7 = 6,
			BUTTON_8 = 7,
			BUTTON_LAST = BUTTON_8,
			BUTTON_LEFT = BUTTON_1,
			BUTTON_RIGHT = BUTTON_2,
			BUTTON_MIDDLE = BUTTON_3,
			NUM_OF_BUTTONS,
		};
	} //namespace mouse

} //namespace gargantua::input