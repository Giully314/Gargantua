/*
gargantua/core/window.ixx

PURPOSE: Manage a window.

CLASSES:
	WindowProperties: pack of parameters associated to the Window.
	Window: Wrapper for GLFW window.


DESCRIPTION:
	This component serves as wrapper for handling glad initialization,
	glfw initialization, shutodown, window events and the update of the window.


TODO:
	-window should be a WindowSystem, that is, a system that handles windows and create
	them.
*/

module;

#include "../vendor/Glad/include/glad/glad.h"
#include "../vendor/glfw/include/GLFW/glfw3.h"


export module gargantua.core.window;

import <string>;
import <functional>;

import gargantua.types;

import gargantua.event.events;


import gargantua.system.event_system;



namespace gargantua::core
{

	//TODO: don't export 
	//Pack the core properties of a Window into this struct. Useful to work with glfw user pointer.
	export struct WindowProperties
	{
		WindowProperties(std::string title_, natural_t width_, natural_t height_) :
			title(std::move(title_)), width(width_), height(height_), event_sys(nullptr), vsync(false)
		{

		}


		std::string title;
		natural_t width;
		natural_t height;
		SharedRes<system::EventSystem> event_sys;
		bool vsync;
	};


	export class Window
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


		auto ListenAndRegisterEvents(SharedRes<system::EventSystem> event_sys) -> void;


		auto SetVSync(bool value) -> void;

		auto IsVSync() const noexcept -> bool
		{
			return properties.vsync;
		}

		//Update the window, swap buffers.
		auto Update() -> void;


		auto GetProperties() const noexcept -> const WindowProperties&
		{
			return properties;
		}

		auto GetHeight() const noexcept -> natural_t
		{
			return properties.height;
		}

		auto GetWidth() const noexcept -> natural_t
		{
			return properties.width;
		}

		auto GetTitle() const noexcept -> std::string_view
		{
			return properties.title;
		}


		auto GetNativeWindow() const noexcept -> GLFWwindow* 
		{ 
			return window; 
		}

	private:
		WindowProperties properties;
		GLFWwindow* window;


		auto ListenToEvents() -> void;
		auto RegisterEvents() -> void;
	}; //class Window

} //namespace gargantua::core

