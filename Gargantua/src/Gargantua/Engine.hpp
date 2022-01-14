#pragma once 

#include "Gargantua/Core/Application.hpp"
#include "Gargantua/Types.hpp"
#include "Gargantua/Time/Stopwatch.hpp"
#include "Gargantua/Event/EventHandler.hpp"

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


		void Run();


	private:
		bool should_close;

		//Current application in execution.
		UniqueRes<Core::Application> app;	
		UniqueRes<Time::Stopwatch> stopwatch;

	};
} //namespace Gargantua