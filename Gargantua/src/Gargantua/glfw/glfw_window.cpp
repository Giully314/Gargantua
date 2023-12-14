/*
* gargantua/glfw/glfw_window.cpp
*/
module;

#include <gargantua/log/logger_macro.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


module gargantua.glfw.window;

import <cstdlib>;

import gargantua.log;
import gargantua.glfw.window_events;
import gargantua.glfw.exceptions;
import gargantua.input.mouse_events;
import gargantua.input.keyboard_events;
import gargantua.input.key_codes;
import gargantua.input.mouse_codes;

namespace gargantua::glfw
{
	Window::Window(const u16 width, const u16 height, const std::string_view title)
		: properties(width, height, title), window(nullptr)
	{
		// TODO: set hints before window creation.

		window = glfwCreateWindow(width, height, title.data(), NULL, NULL);

		if (!window)
		{
			throw WindowConstructionError{};
		}

		// Update the current context with this window
		// TODO: for multiple windows? 
		glfwMakeContextCurrent(window);

		// TODO: is it the right place to init glad? 
		i32 glad_initialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!glad_initialized)
		{
			GRG_CORE_ERROR("Error while initializing glad.");
			// Exit failure.
			std::exit(1);
		}

		glfwSetWindowUserPointer(window, static_cast<void*>(&properties));

		//SetVsync(true);

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
					properties.event_dispatcher->Dispatch<input::KeyPressedEvent>(static_cast<input::Key>(key));
					break;
				case GLFW_RELEASE:
					properties.event_dispatcher->Dispatch<input::KeyReleasedEvent>(static_cast<input::Key>(key));
					break;
				case GLFW_REPEAT:
					properties.event_dispatcher->Dispatch<input::KeyPressedEvent>(static_cast<input::Key>(key));
					break;
				}
			});


		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

				properties.event_dispatcher->Dispatch<input::MouseCursorEvent>(static_cast<f32>(xpos), static_cast<f32>(ypos));
			});


		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
					properties.event_dispatcher->Dispatch<input::MouseButtonPressedEvent>(
						static_cast<input::MouseButton>(button));
					break;
				case GLFW_RELEASE:
					properties.event_dispatcher->Dispatch<input::MouseButtonReleasedEvent>(
						static_cast<input::MouseButton>(button));
					break;
				}
			});


		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowProperties& properties = *static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

				properties.event_dispatcher->Dispatch<input::MouseWheelScrollEvent>(static_cast<f32>(yoffset));
			});
	}

} // namespace gargantua::glfw