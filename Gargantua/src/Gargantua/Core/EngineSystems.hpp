#pragma once
/*
Gargantua/Core/EngineSystems.hpp

PURPOSE: Pack the engine system into a struct held by the application.

CLASSES:
	EngineSystems: Pointers to systems.


DESCRIPTION:
	The systems are managed by the engine class; this fact is reinforced by the SharedRes concept.
	So the application has the flexibility to interact with the "low level" part of the engine
	but MUST not access the lifetime of a system.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Systems/EventSystem.hpp"
#include "Gargantua/Systems/InputSystem.hpp"
#include "Gargantua/Systems/Renderer2dSystem.hpp"
#include "Gargantua/Systems/ShaderSystem.hpp"
#include "Gargantua/Systems/ECSSystem.hpp"
#include "Gargantua/Systems/TimeSystem.hpp"

#include "Gargantua/Settings.hpp"


namespace Gargantua
{
	namespace Core
	{
		struct EngineSystems
		{
			SharedRes<Systems::EventSystem> engine_event_sys;
			SharedRes<Systems::EventSystem> app_event_sys;
			SharedRes<Systems::Renderer2dSystem> renderer2d_sys;
			SharedRes<Systems::ShaderSystem> shader_sys;
			SharedRes<Systems::ECSSystem<ListOfComponents, ListOfSystems>> ecs_sys;
			SharedRes<Systems::TimeSystem> time_sys;
		};
	} //namespace Core 
} //namespace Gargantua