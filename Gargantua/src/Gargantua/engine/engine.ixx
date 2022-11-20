/*
gargantua/engine/engine.ixx

PURPOSE: Engine. Make the all systems to work together.

CLASSES:
	Engine: The whole brain.


DESCRIPTION:
	This class is more than simple glue code for the systems and other components;
	it's like the central nervous system.
	Entry point of the engine.
	Controls the initialization of every system and component.
	Provide the game loop.


TODO:
	clean up the code (expecially in the constructor). Too much code in a single function, bad readability.


*/

export module gargantua.engine.engine;

import <functional>;

import gargantua.types;

import gargantua.core.core;

import gargantua.system.system;

import gargantua.imgui.imgui_stage;


namespace gargantua::engine
{

	export class Engine
	{
	public:
		Engine(std::function<core::Application* (void)> create_app);
		Engine(std::function<core::Application* (void)> create_app, natural_t width, natural_t height);

		~Engine();


		SharedRes<core::Window> GetWindow() const noexcept
		{
			return window;
		}


		void Run();


	private:
		bool should_close;

		//Current application in execution.
		UniqueRes<core::Application> app;
		SharedRes<core::Window> window;


		//Use the Enginesystems struct?
		UniqueRes<system::LoggerSystem> engine_logger;
		SharedRes<system::EventSystem> engine_event_sys;
		SharedRes<system::EventSystem> app_event_sys;
		SharedRes<system::InputSystem> input_sys;
		SharedRes<system::Renderer2dSystem> renderer2d_sys;
		SharedRes<system::ShaderSystem> shader_sys;
		SharedRes<system::TimeSystem> time_sys;

		//SharedRes<core::Scene2d> scene2d;

		UniqueRes<imgui::ImGuiStage> gui_stage;
	}; //class Engine
} //namespace gargantua::engine