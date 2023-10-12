/*
* gargantua/platform/window.cpp
*/
module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>

module gargantua.platform.window;

import gargantua.platform.platform_events;

namespace gargantua::platform
{
	Window::Window(const u16 width, const u16 height, std::string_view title) 
		: properties(width, height, title), window(nullptr)
	{
		// TODO: set hints before window creation.

		window = glfwCreateWindow(width, height, title.data(), NULL, NULL);

		if (!window)
		{
			throw;
		}

		// Update the current context with this window
		// TODO: for multiple windows? 
		glfwMakeContextCurrent(window);

		i32 glad_initialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!glad_initialized)
		{
			// log info
			std::exit(EXIT_FAILURE);
		}

		glfwSetWindowUserPointer(window, static_cast<void*>(&properties));

		SetVsync(true);

		RegisterEventsCallbacks();
	}


	Window::~Window()
	{
		glfwDestroyWindow(window);
	}


	auto Window::RegisterEventsCallbacks() -> void
	{
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));
				properties.event_dispatcher->Dispatch<WindowResizeEvent>(static_cast<u32>(width), static_cast<u32>(height));
			});


		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

				properties.event_dispatcher->Dispatch<WindowCloseEvent>(true);
			});


		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
					properties.event_dispatcher->Dispatch<KeyPressedEvent>(static_cast<Key>(key));
					break;
				case GLFW_RELEASE:
					properties.event_dispatcher->Dispatch<KeyReleasedEvent>(static_cast<Key>(key));
					break;
				case GLFW_REPEAT:
					properties.event_dispatcher->Dispatch<KeyPressedEvent>(static_cast<Key>(key));
					break;
				}
			});


		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

				properties.event_dispatcher->Dispatch<MouseCursorEvent>(static_cast<f32>(xpos), static_cast<f32>(ypos));
			});


		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
					properties.event_dispatcher->Dispatch<MouseButtonPressedEvent>(static_cast<MouseButton>(button));
					break;
				case GLFW_RELEASE:
					properties.event_dispatcher->Dispatch<MouseButtonReleasedEvent>(static_cast<MouseButton>(button));
					break;
				}
			});


		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

				properties.event_dispatcher->Dispatch<MouseWheelScrollEvent>(static_cast<f32>(yoffset));
			});
	}

} // namespace gargantua::platform