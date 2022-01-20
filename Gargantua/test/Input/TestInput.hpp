#pragma once

#include "../GargantuaTest.hpp"

#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Types.hpp"
#include "Gargantua/Core/InputState.hpp"
#include "Gargantua/Core/Window.hpp"
#include "Gargantua/Event/EventListenerSystem.hpp"
#include "Gargantua/Event/EventRegisterSystem.hpp"
#include "Gargantua/Event/WindowEvents.hpp"
#include "Gargantua/Event/KeyEvents.hpp"
#include "Gargantua/Core/EventSystem.hpp"

namespace Gargantua
{
	namespace Test
	{
		class TestInput final : public GargantuaTest
		{
		public:

			void Create() override
			{
				event_sys = CreateUniqueRes<Core::EventSystem>();
				window = CreateUniqueRes<Core::Window>("TestWindow", 480, 360);
				input = CreateUniqueRes<Core::InputState>();
				
				window->ListenToEvents(event_sys->GetEventListenerSystem());
				window->RegisterEvents(event_sys->GetEventRegisterSystem());

				input->ListenToEvents(event_sys->GetEventListenerSystem());
			}

			void Destroy() override
			{
				window.reset();
				input.reset();
			}

			void RunTest() override
			{
				Create();

				bool close = false;

				event_sys->GetEventListenerSystem()->RegisterListener<Event::WindowCloseEvent>([&](
					const Event::BaseEvent& e)
					{
						close = true;
					});

				event_sys->GetEventListenerSystem()->RegisterListener<Event::KeyPressedEvent>([](
					const Event::BaseEvent& e)
					{
						const auto& ie = static_cast<const Event::KeyPressedEvent&>(e);
						GRG_CORE_DEBUG("Key pressed {}", ie.key_code);
					});

				while (!close)
				{
					window->Update();
					event_sys->ProcessEvents();
				}

				Destroy();
			}

		private:
			UniqueRes<Core::Window> window;
			UniqueRes<Core::InputState> input;
			UniqueRes<Core::EventSystem> event_sys;
		};
	}
}