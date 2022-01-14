#pragma once

//#include "../vendor/Glad/include/glad/glad.h"
#include "../vendor/glfw/include/GLFW/glfw3.h"



#include "Gargantua/Types.hpp"
#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Concepts/Event.hpp"
#include "Gargantua/Event/EventHandler.hpp"
#include "Gargantua/Event/WindowEvents.hpp"
#include "Gargantua/Event/KeyEvents.hpp"
#include "Gargantua/Event/MouseEvents.hpp"

#include <string>
#include <functional>

namespace Gargantua
{
	namespace Core
	{
		struct WindowProperties
		{
			WindowProperties(std::string title_, natural_t width_, natural_t height_) :
				title(std::move(title_)), width(width_), height(height_), event_handler(nullptr)
			{

			}


			template <Concepts::Event T, typename... Args>
			void RegisterWindowEvent(Args&& ...args)
			{
				event_handler->RegisterEvent<T>(std::move(args)...);
			}

			std::string title;
			natural_t width;
			natural_t height;
			Event::EventHandler* event_handler;
		};


		//TODO: Set VSync
		class Window
		{
		public:

			Window();
			Window(std::string title, natural_t width, natural_t height, Event::EventHandler* event_handler);
			~Window();


			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;
			Window(Window&&) = delete;
			Window& operator=(Window&&) = delete;

			void Update();


			inline void SetEventHandler(Event::EventHandler* event_handler)
			{
				properties.event_handler = event_handler;
			}


			inline const WindowProperties& GetProperties() const noexcept
			{
				return properties;
			}

			inline natural_t GetHeight() const noexcept
			{
				return properties.height;
			}

			inline natural_t GetWidth() const noexcept
			{
				return properties.width;
			}

			inline std::string_view GetTitle() const noexcept
			{
				return properties.title;
			}

		private:
			WindowProperties properties;
			GLFWwindow* window;


			void Init();
			void Shutdown();
			void SetCallbacks();
		};
	} //namespace Core
} //namespace Gargantua

