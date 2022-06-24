#pragma once
/*
Gargantua/Core/Scene2d.hpp

PURPOSE: information about the scene.

CLASSES:
	Scene2d: struct for packing information about the current scene.

DESCRIPTION:
	Represent the scene. The coordinate system has positive x values from left to right; has positive y values from
	top to bottom.

*/

#include "Gargantua/Settings.hpp"
#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Mat4d.hpp"

#include "Gargantua/Systems/ECSSystem.hpp"

#include "Gargantua/ECS/Types.hpp"


namespace Gargantua
{
	namespace Core
	{
		class Scene2d
		{

		private:
			//Current camera used to see the 2d scene.
			ECS::Entity camera;


			SharedRes<Systems::ECSSystem<ListOfComponents, ListOfSystems>> ecs_sys;


			//Current camera matrix. To set with BeginScene.
			Math::Mat4df proj_view;
		};
	} //namespace Core
} //namespace Gargantua