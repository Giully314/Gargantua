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
* - Monitor events.
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
		explicit WindowProperties(const u16 width_, const u16 height_, std::string_view title_) : 
									WindowProperties(width_, height_, title_, nullptr)
		{

		}

		explicit WindowProperties(const u16 width_, const u16 height_, std::string_view title_,
									shared_res<PlatformEventDispatcher> event_dispatcher_) :
			width(width_), height(height_), title(title_), vsync(false), event_dispatcher(std::move(event_dispatcher_))
		{

		}

		u16 width;
		u16 height;
		std::string title;
		bool vsync;
		shared_res<PlatformEventDispatcher> event_dispatcher;
	};


	class Window
	{
	public:
		// Create a window with the specified width, height and title.
		// Precondition: the library glfw must be initialized before contructing Window.
		// Can throw if the creation of the window has errors.
		Window(const u16 width, const u16 height, std::string_view title);
		Window(const u16 width, const u16 height, std::string_view title, 
				shared_res<PlatformEventDispatcher> event_dispatcher);

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Window(Window&&) = default;
		Window& operator=(Window&&) = default;

		~Window();
		
		// Update the window swapping buffers.
		auto Update() -> void
		{
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		// 
		auto SetVsync(bool set_vsync) -> void
		{
			glfwSwapInterval(set_vsync ? 1 : 0);
			properties.vsync = set_vsync;
		}


		auto SetEventDispatcher(shared_res<PlatformEventDispatcher> event_dispatcher) -> void
		{
			properties.event_dispatcher = std::move(event_dispatcher);
		}
		
		auto GetProperties() const noexcept -> const WindowProperties&
		{
			return properties;
		}


		auto RegisterEvents() -> void;

	private:
		GLFWwindow* window;
		WindowProperties properties;
	};
} // namespace gargantua::platform
