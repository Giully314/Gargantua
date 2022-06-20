/*
Gargantua/Physics/ReferenceFrame.cpp
*/
#include "ReferenceFrame.hpp"


namespace Gargantua
{
	namespace Physics
	{
		Math::Vec2df ReferenceFrame::origin{ 0.0f, 0.0f };
		Math::Vec2df ReferenceFrame::i_dir{ 1.0f, 0.0f };
		Math::Vec2df ReferenceFrame::j_dir{ 0.0f, 1.0f };
	} //namespace Physics
} //namespace Gargantua