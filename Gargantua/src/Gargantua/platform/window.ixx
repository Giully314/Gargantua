/* 
* gargantua/platform/window.ixx
* 
* PURPOSE:
* 
* CLASSES:
*	WindowProperties:
*	Window: 
* 
* DESCRIPTION:
* The Window class implements RAII for the GLFWwindow.
* 
* TODO: 
* - Share context between multiple windows.
* - 
* 
*/

module;

#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module gargantua.platform.window;

import <utility>;
import <string>;
import <string_view>;

import gargantua.types;
import gargantua.platform.event_dispatcher;


export namespace gargantua::platform
{
	struct WindowProperties
	{
		explicit WindowProperties(const u16 width_, const u16 height_, std::string_view title_)
			: width(width_), height(height_), title(title_), vsync(false)
		{
			event_dispatcher = &PlatformEventDispatcher::Instance();
		}

		u16 width;
		u16 height;
		std::string title;
		bool vsync;
		non_owned_res<PlatformEventDispatcher> event_dispatcher;
	};


	class Window
	{
	public:
		// Create a window with the specified width, height and title.
		// Precondition: the library glfw must be initialized before contructing Window.
		// Can throw if the creation of the window has errors.
		//Window(const u16 width, const u16 height, std::string_view title);
		Window(const u16 width, const u16 height, std::string_view title);

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Window(Window&&) = default;
		Window& operator=(Window&&) = default;

		~Window();
		
		// Update the window swapping buffers.
		auto Update() -> void
		{
			glfwSwapBuffers(window);
		}

		// 
		auto SetVsync(bool set_vsync) -> void
		{
			glfwSwapInterval(set_vsync ? 1 : 0);
			properties.vsync = set_vsync;
		}

		auto GetProperties() const noexcept -> const WindowProperties&
		{
			return properties;
		}


		auto GetNative() -> non_owned_res<GLFWwindow>
		{
			return window;
		}


		auto GetHeight() const noexcept -> u32
		{
			return properties.height;
		}

		auto GetWidth() const noexcept -> u32
		{
			return properties.width;
		}

	private:
		GLFWwindow* window;
		WindowProperties properties;

		auto RegisterEventsCallbacks() -> void;
	};
} // namespace gargantua::platform
