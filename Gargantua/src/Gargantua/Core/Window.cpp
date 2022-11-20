/*
Gargantua/Core/Window.cpp
*/

module;

#include "../vendor/Glad/include/glad/glad.h"
#include "../vendor/glfw/include/GLFW/glfw3.h"


module gargantua.core.window;

import <string>;

namespace gargantua::core
{
	Window::Window() : Window("", 1, 1)
	{

	}

	Window::Window(std::string title, natural_t width, natural_t height) :
		properties(title, width, height), window(nullptr)
	{
		int status = glfwInit();

		if (not status) [[unlikely]]
		{
			//GRG_CORE_ERROR("GLFW initialization failed.");
			throw;
		}


		//GRG_CORE_DEBUG("Creating window");
		window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, NULL);

		if (not window) [[unlikely]]
		{
			throw;
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &properties);


		//This must be called after setting window the current context
		if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) [[unlikely]]
		{
			//GRG_CORE_ERROR("Failed to initialize GLAD");
			throw;
		}
	}


	Window::~Window()
	{
		if (window) [[likely]]
		{
			glfwDestroyWindow(window);
		}
		glfwTerminate();
	}


	auto Window::Update() -> void
	{
		/*GRG_CORE_DEBUG("Window Update. Window size {} {}", properties.width, properties.height);*/
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	auto Window::SetVSync(bool value) -> void
	{
		if (value)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		properties.vsync = value;
	}



	auto Window::ListenAndRegisterEvents(SharedRes<system::EventSystem> event_sys) -> void
	{
		properties.event_sys = std::move(event_sys);
		ListenToEvents();
		RegisterEvents();
	}


	auto Window::ListenToEvents() -> void
	{
		properties.event_sys->RegisterListener<event::WindowResizeEvent>([this](const event::BaseEvent& e)
			{
				const event::WindowResizeEvent& we = static_cast<const event::WindowResizeEvent&>(e);
				properties.width = we.new_width;
				properties.height = we.new_height;
			});
	}

	auto Window::RegisterEvents() -> void
	{
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
				props.event_sys->RegisterEvent<event::WindowResizeEvent>(width, height);
			});


		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				props.event_sys->RegisterEvent<event::WindowCloseEvent>(true);
			});


		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
					props.event_sys->RegisterEvent<event::KeyPressedEvent>(key);
					break;
				case GLFW_RELEASE:
					props.event_sys->RegisterEvent<event::KeyReleasedEvent>(key);
					break;
				case GLFW_REPEAT:
					props.event_sys->RegisterEvent<event::KeyPressedEvent>(key);
					break;
				}
			});


		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				props.event_sys->RegisterEvent<event::MouseCursorEvent>((float)xpos, (float)ypos);
			});


		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
					props.event_sys->RegisterEvent<event::MouseButtonPressedEvent>(button);
					break;
				case GLFW_RELEASE:
					props.event_sys->RegisterEvent<event::MouseButtonReleasedEvent>(button);
					break;
				}
			});


		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

				props.event_sys->RegisterEvent<event::MouseWheelScrollEvent>((real_t)yoffset);
			});
	}

} //namespace gargantua::core