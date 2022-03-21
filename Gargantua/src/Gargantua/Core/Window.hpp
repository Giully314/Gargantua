#pragma once
/*
Gargantua/Core/Window.hpp

PURPOSE: Manage a window.

CLASSES:
	WindowProperties: pack of parameters associated to the Window.
	Window: Wrapper for GLFW window.


DESCRIPTION:
	This component serves as wrapper for handling glad initialization, 
	glfw initialization, shutodown, window events and the update of the window.
*/


#include "../vendor/Glad/include/glad/glad.h"
#include "../vendor/glfw/include/GLFW/glfw3.h"



#include "Gargantua/Types.hpp"
#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Concepts/Event.hpp"
#include "Gargantua/Event/EventRegisterSystem.hpp"
#include "Gargantua/Event/EventListenerSystem.hpp"
#include "Gargantua/Event/WindowEvents.hpp"
#include "Gargantua/Event/KeyEvents.hpp"
#include "Gargantua/Event/MouseEvents.hpp"

#include <string>
#include <functional>

namespace Gargantua
{
	namespace Core
	{

		//Pack the core properties of a Window into this struct. Useful to work with glfw user pointer.
		struct WindowProperties
		{
			WindowProperties(std::string title_, natural_t width_, natural_t height_) :
				title(std::move(title_)), width(width_), height(height_), event_reg_sys(nullptr),
				event_list_sys(nullptr), vsync(false)
			{

			}


			std::string title;
			natural_t width;
			natural_t height;
			NonOwnedRes<Event::EventRegisterSystem> event_reg_sys;
			NonOwnedRes<Event::EventListenerSystem> event_list_sys;
			bool vsync;
		};


		class Window
		{
		public:

			//Initialize glfw, glad and create the window.
			Window();
			Window(std::string title, natural_t width, natural_t height);
			
			//Destroy the window and shutdown glfw.
			~Window();


			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;
			Window(Window&&) = default;
			Window& operator=(Window&&) = default;


			
			void ListenToEvents(NonOwnedRes<Event::EventListenerSystem> event_list_sys);

			void RegisterEvents(NonOwnedRes<Event::EventRegisterSystem> event_reg_sys);


			void SetVSync(bool value);
			
			inline bool IsVSync() const noexcept 
			{
				return properties.vsync;
			}

			//Update the window, swap buffers.
			void Update();


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


			inline GLFWwindow* GetNativeWindow() const noexcept { return window; }

		private:
			WindowProperties properties;
			GLFWwindow* window;
		};
	} //namespace Core
} //namespace Gargantua

