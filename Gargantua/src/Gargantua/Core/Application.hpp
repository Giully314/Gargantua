#pragma once


#include "Gargantua/Time/TimeStep.hpp"


namespace Gargantua
{
	namespace Core
	{
		/*
		Interface for the creation of an Application.
		*/
		class Application
		{
		public:
			Application() = default;

			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;

			Application(Application&&) = delete;
			Application& operator=(Application&&) = delete;

			virtual ~Application() = default;


			/*
			This function is called at the start of the Run method from Engine.
			Note that this function doesn't replace the role of constructor.
			*/
			virtual void Start() = 0;
			
			
			/*
			This function is called at the end of the Run method from Engine.
			Note that this function doesn't replace the role of destructor.
			*/
			virtual void Shutdown() = 0;


			/*
			Reset the application. Is safe to call this function before Shutdown? 
			Think about it
			*/
			virtual void Reset() = 0;


			/*
			Execute should perform a single "tick" of the app. A tick is a single update of the app with
			a delta time.
			*/
			virtual void Execute(const Time::TimeStep&) = 0;
		};


	} //namespace Core
} //namespace Gargantua