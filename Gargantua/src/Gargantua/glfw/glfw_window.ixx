/*
* gargantua/glfw/glfw_window.ixx
* 
* PURPOSE: Manage a glfw window.
*
* CLASSES:
*	WindowProperties: info about the window.
*	Window: RAII for a glfw window.
*
* DESCRIPTION:
*	This component manage all the funcionalities of a GLFWwindow using a RAII wrapper class. 
*	The Window class is registered to the engine event system to dispatch events related to the window
*	and input.
*
* 
* USAGE:
*	unique_res<Window> window;
*	try
*	{
*		window = CreateUniqueRes<Window>(args...);
*	}
*	catch (...)
*	{
*	
*	}
*	
*	
* 
* TODO:
* - Share context between multiple windows.
*/

module;

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module gargantua.glfw.window;

import <string_view>;
import <string>;

import gargantua.types;
import gargantua.event.event_dispatcher;
import gargantua.event.engine_event_dispatcher;

export namespace gargantua::glfw
{
	struct WindowProperties
	{
		explicit WindowProperties(const u16 width_, const u16 height_, const std::string_view title_)
			: width(width_), height(height_), title(title_), vsync(false)
		{
			event_dispatcher = &event::EngineEventDispatcher();
		}

		u16 width;
		u16 height;
		std::string title;
		bool vsync;
		non_owned_res<event::EventDispatcher> event_dispatcher;
	};


	class Window : NonCopyable
	{
	public:
		/*
		* Create a window with the specified width, height and title.
		* Precondition: the library glfw must be initialized before contructing Window.
		* Can throw if the creation of the window has errors.
		*/
		Window(const u16 width, const u16 height, const std::string_view title);

		Window(Window&&) = default;
		Window& operator=(Window&&) = default;

		~Window();


		// Update the window swapping buffers.
		auto Update() -> void
		{
			glfwSwapBuffers(window);
		}

		
		auto SetVsync(const bool set_vsync) -> void
		{
			glfwSwapInterval(set_vsync ? 1 : 0);
			properties.vsync = set_vsync;
		}


		[[nodiscard]]
		auto Properties() const noexcept -> const WindowProperties&
		{
			return properties;
		}


		/*
		* Return a pointer to the GLFWwindow.
		*/
		[[nodiscard]]
		auto Native() -> non_owned_res<GLFWwindow>
		{
			return window;
		}

		[[nodiscard]]
		constexpr auto Height() const noexcept -> u32
		{
			return properties.height;
		}


		[[nodiscard]]
		constexpr auto Width() const noexcept -> u32
		{
			return properties.width;
		}

	private:
		GLFWwindow* window;
		WindowProperties properties;

		auto RegisterEventsCallbacks() -> void;
	};

} // namespace gargantua::glfw