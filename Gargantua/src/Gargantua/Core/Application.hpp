#pragma once


#include "Gargantua/Time/TimeStep.hpp"
#include "Gargantua/Core/Pipeline.hpp"
#include "Gargantua/Core/EventSystem.hpp"
//#include "Gargantua/Core/ImGuiStage.hpp"

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

			virtual ~Application();


			/*
			This function is called at the start of the Run method from Engine.
			Note that this function doesn't replace the role of constructor.
			This function could be used to initialize the stages, register listeners and events and so on.
			*/
			virtual void Start() = 0;
			
			
			/*
			This function is called at the end of the Run method from Engine.
			Note that this function doesn't replace the role of destructor.
			*/
			virtual void Shutdown() = 0;


			/*
			Reset the application. Is safe to call this function before Shutdown? 
			Think about it. Maybe this method is useless.
			*/
			//virtual void Reset() = 0;


			/*
			Loop through the pipeline and execute every stage. 
			*/
			void Execute(const Time::TimeStep&);


			/*
			Call RenderGUI for every stage.
			*/
			void RenderGUI();


		protected:
			Pipeline pipeline;
			EventSystem app_event_system;
		};


	} //namespace Core
} //namespace Gargantua