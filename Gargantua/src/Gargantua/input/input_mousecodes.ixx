/*
* gargantua/input/input_mousecodes.ixx
*
* PURPOSE: Define mouse button codes.
* 
* CLASSES:
*	MouseButton: enum for the codes of the buttons.
*/

export module gargantua.input.mouse_codes;

import gargantua.types;

namespace gargantua::input
{
	//From glfw3.h
	export enum class MouseButton : mouse_t
	{
		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,
		ButtonLast = Button8,
		ButtonLeft = Button1,
		ButtonRight = Button2,
		ButtonMiddle = Button3,
		NumOfButtons,
	};
} //namespace gargantua::input