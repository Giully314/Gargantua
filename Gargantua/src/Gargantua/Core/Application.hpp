#pragma once
/*
Gargantua/Core/Application.hpp

PURPOSE: Define the skeleton of an application.

CLASSES:
	Application: Base class for the application defined from user.


DESCRIPTION:
	This class is contained and controlled inside the Engine.
	An Application is "what" happens, the Engine is "how" happens.
	At the core, there is the Pipeline object that defines the order of execution of the 
	stages (the building block of the Application).

USAGE:
	class MyApplication : public Gargantua::Core::Application
	{
		void Start() override
		{
			pipeline.AddStage<MyStage>();
		}


		void Shutdown() override
		{
		}
	}

	Gargantua::Engine e {[](){return new MyApplication();}, width, height};
*/

#include "Gargantua/Core/Pipeline.hpp"
#include "Gargantua/Core/EngineSystems.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Types.hpp"

namespace Gargantua
{
	namespace Core
	{
		class Application : private NonCopyable
		{
		public:
			Application() = default;

			Application(Application&&) = default;
			Application& operator=(Application&&) = default;

			virtual ~Application() = default;


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


			inline EngineSystems& GetEngineSystems() noexcept 
			{
				return systems;
			}


		protected:
			Pipeline pipeline;
			EngineSystems systems;
		};
	} //namespace Core
} //namespace Gargantua