#include "Window.hpp"


namespace Gargantua
{
	namespace Core
	{
		Window::Window() : Window("", 1, 1, nullptr)
		{

		}

		Window::Window(std::string title, natural_t width, natural_t height, Event::EventHandler* event_handler) :
			properties(title, width, height), window(nullptr)
		{
			SetEventHandler(event_handler);
			Init();
		}


		Window::~Window()
		{
			Shutdown();
		}


		void Window::Update()
		{
			glfwPollEvents();
			glfwSwapBuffers(window);
			GRG_CORE_DEBUG("window size: {} {}", properties.width, properties.height);
		}


		void Window::Init()
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
			/*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				GRG_CORE_ERROR("Failed to initialize GLAD");
				throw;
			}*/


			if (properties.event_handler)
			{
				SetCallbacks();
			}
		}


		void Window::Shutdown()
		{
			if (window)
			{
				glfwDestroyWindow(window);
			}
			glfwTerminate();
		}


		void Window::SetCallbacks()
		{
			glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
					props.RegisterWindowEvent<Event::WindowResizeEvent>(width, height);
				});


			glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

					props.RegisterWindowEvent<Event::WindowCloseEvent>(true);
				});


			glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

					switch (action)
					{
					case GLFW_PRESS:
						props.RegisterWindowEvent<Event::KeyPressedEvent>(key);
						break;
					case GLFW_RELEASE:
						props.RegisterWindowEvent<Event::KeyReleasedEvent>(key);
						break;
					case GLFW_REPEAT:
						props.RegisterWindowEvent<Event::KeyPressedEvent>(key);
						break;
					}
				});


			glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

					props.RegisterWindowEvent<Event::MouseCursorEvent>((float)xpos, (float)ypos);
				});


			glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
				{
					WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);

					switch (action)
					{
					case GLFW_PRESS:
						props.RegisterWindowEvent<Event::MouseButtonPressedEvent>(button);
						break;
					case GLFW_RELEASE:
						props.RegisterWindowEvent<Event::MouseButtonReleasedEvent>(button);
						break;
					}
				});


			Event::EventHandler& event_handler = *(properties.event_handler);

			event_handler.RegisterListener<Event::WindowResizeEvent>([this](const Event::BaseEvent& e)
				{
					const Event::WindowResizeEvent& we = static_cast<const Event::WindowResizeEvent&>(e);
					properties.width = we.new_width;
					properties.height = we.new_height;
				});
		}
	}
}