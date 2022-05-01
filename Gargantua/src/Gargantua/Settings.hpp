#pragma once
/*
Gargantua/Settings.hpp


PURPOSE: Settings for ECS.


*/


#include "Gargantua/MPL/TypeList.hpp"

#include "Gargantua/Renderer/RendererComponents.hpp"

#include "Gargantua/Physics/NewtonianSystem.hpp"
#include "Gargantua/Physics/PhysicsComponents.hpp"

namespace Gargantua
{
	using ListOfComponents = MPL::TypeList<Physics::TransformComponent, 
		Renderer::SpriteComponent, Renderer::OrthoCameraComponent>;

	using ListOfSystems = MPL::TypeList<Physics::NewtonianSystem>;
	
} //namespace Gargantua