#pragma once
/*
Gargantua/Input/MouseCodes.hpp

PURPOSE: Codes for buttons of the mouse.

CLASSES:

DESCRIPTION:

USAGE:

*/

#include "Gargantua/Types.hpp"

namespace Gargantua
{
	namespace Input 
	{
		namespace Mouse
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
		} //namespace Mouse
	} //namespace Input
} //namespace Gargantua