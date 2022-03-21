#pragma once
/*
Gargantua/Core/EngineSystems.hpp

PURPOSE: Pack the engine system into a struct held by the application.

CLASSES:
	EngineSystems: Pointers to systems.


DESCRIPTION:
	The systems are managed by the engine class; this fact is reinforced by the NonOwnedRes concept.
	So the application has the flexibility to interact with the "low level" part of the engine
	but MUST not access the lifetime of a system.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Systems/EventSystem.hpp"
#include "Gargantua/Systems/InputSystem.hpp"
#include "Gargantua/Systems/RendererSystem.hpp"


namespace Gargantua
{
	namespace Core
	{
		struct EngineSystems
		{
			//Or maybe is better SharedRes?
			SharedRes<Systems::EventSystem> engine_event_sys;
			SharedRes<Systems::EventSystem> app_event_sys;
			SharedRes<Systems::RendererSystem> renderer_sys;
		};
	} //namespace Core 
} //namespace Gargantua