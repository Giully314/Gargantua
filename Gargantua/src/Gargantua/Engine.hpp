#pragma once 

#include "Gargantua/Types.hpp"

#include "Gargantua/Time/Stopwatch.hpp"

#include "Gargantua/Core/Application.hpp"
#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Core/EventSystem.hpp"
#include "Gargantua/Core/Window.hpp"
#include "Gargantua/Core/InputState.hpp"
#include "Gargantua/Core/ImGuiStage.hpp"

#include <functional>



namespace Gargantua
{
	/*
	This class is the entry point of the engine. Initialize all the basic systems (logger, threadpool, ecc), provides basic operations,
	handles application loop and so on.
	*/
	class Engine
	{
	public:
		Engine(std::function<Core::Application*(void)> create_app);
		~Engine();


		inline NonOwnedRes<Core::Window> GetWindow() const noexcept 
		{
			return window.get();
		}


		void Run();


	private:
		bool should_close;

		//Current application in execution.
		UniqueRes<Core::Application> app;	
		UniqueRes<Time::Stopwatch> stopwatch;
		UniqueRes<Core::EngineLogger> engine_logger;
		UniqueRes<Core::EventSystem> engine_event_system;
		UniqueRes<Core::Window> window;
		UniqueRes<Core::InputState> input_state;

		UniqueRes<Core::ImGuiStage> gui_stage;
	};
} //namespace Gargantua