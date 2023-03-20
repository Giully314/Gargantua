/*
* gargantua/platform/mouse_codes.ixx
*
* PURPOSE: Define mouse button codes.
* 
* CLASSES:
*	MouseButton: enum for the codes of the buttons.
* 
* DESCRIPTION:
*/

export module gargantua.platform.mouse_codes;

import gargantua.types;

export namespace gargantua::platform
{
	//From glfw3.h
	enum class MouseButton : mouse_t
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

} //namespace gargantua::platform