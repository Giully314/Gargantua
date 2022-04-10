#pragma once
/*
Gargantua/Core/Scene2d.hpp

PURPOSE: information about the scene.

CLASSES:
	Scene2d: struct for packing information about the current scene.

TODO: this is (probably) a temporary solution.

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