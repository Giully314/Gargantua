#pragma once
/*
Gargantua/Core/Scene2d.hpp


*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Mat4d.hpp"

namespace Gargantua
{
	namespace Core
	{
		struct Scene2d
		{
			//Current camera matrix. To set with BeginScene.
			Math::Mat4df proj_view;
		};
	} //namespace Core
} //namespace Gargantua