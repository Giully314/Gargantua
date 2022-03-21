/*
Gargantua/Core/Window.cpp
*/
#include "Window.hpp"


namespace Gargantua
{
	namespace Core
	{
		Window::Window() : Window("", 1, 1)
		{

		}

		Window::Window(std::string title, natural_t width, natural_t height) :
			properties(title, width, height), window(nullptr)
		{
			int status = glfwInit();

			if (!status)
			{
				GRG_CORE_ERROR("GLFW initialization failed.");
				throw;
			}


			GRG_CORE_DEBUG("Creating window");
			window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), NULL, NULL);

			if (!window)
			{
				throw;
			}

			glfwMakeContextCurrent(window);
			glfwSetWindowUserPointer(window, &properties);


			//This must be called after setting window the current context
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				GRG_CORE_ERROR("Failed to initialize GLAD");
				throw;
			}
		}


		Window::~Window()
		{
			if (window)
			{
				glfwDestroyWindow(window);
			}
			glfwTerminate();
		}


		void Window::Update()
		{
			/*GRG_CORE_DEBUG("Window Update. Window size {} {}", properties.width, properties.height);*/
			glfwPollEvents();
			glfwSwapBuffers(window);
		}


		void Window::SetVSync(bool value)
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



		void Window::ListenToEvents(NonOwnedRes<Event::EventListenerSystem> event_list_sys)
		{
			properties.event_list_sys = event_list_sys;
			event_list_sys->RegisterListener<Event::WindowResizeEvent>([this](const Event::BaseEvent& e)
				{
					const Event::WindowResizeEvent& we = static_cast<const Event::WindowResizeEvent&>(e);
					properties.width = we.new_width;
					properties.height = we.new_height;
				});
		}

		void Window::RegisterEvents(NonOwnedRes<Event::EventRegisterSystem> event_reg_sys)
		{
			properties.event_reg_sys = event_reg_sys;

			glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
					props.event_reg_sys->RegisterEvent<Event::WindowResizeEvent>(width, height);
				});


			glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

					props.event_reg_sys->RegisterEvent<Event::WindowCloseEvent>(true);
				});


			glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

					switch (action)
					{
					case GLFW_PRESS:
						props.event_reg_sys->RegisterEvent<Event::KeyPressedEvent>(key);
						break;
					case GLFW_RELEASE:
						props.event_reg_sys->RegisterEvent<Event::KeyReleasedEvent>(key);
						break;
					case GLFW_REPEAT:
						props.event_reg_sys->RegisterEvent<Event::KeyPressedEvent>(key);
						break;
					}
				});


			glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

					props.event_reg_sys->RegisterEvent<Event::MouseCursorEvent>((float)xpos, (float)ypos);
				});


			glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

					switch (action)
					{
					case GLFW_PRESS:
						props.event_reg_sys->RegisterEvent<Event::MouseButtonPressedEvent>(button);
						break;
					case GLFW_RELEASE:
						props.event_reg_sys->RegisterEvent<Event::MouseButtonReleasedEvent>(button);
						break;
					}
				});
		}
	} //namespace Core
} //namespace Gargantua