/*
* gargantua/app/application.ixx
* 
* PURPOSE: Application executed by the engine.
* 
* CLASSES:
*	Application: Define the API of an application executed by the engine.
* 
* DESCRIPTION:
*	The Application class is an abstract class used to define the API used by 
*	the engine for the execution of an app. The user must only override the Run method
*	and pass the class to start experimenting with games! 
* 
* 
* USAGE:
*	For more info, see GargantuaEditor and TestApp in Sandbox.
* 
*	class MyApp : public Application
*	{
*	public:
*		// Override methods.
*		
*		// Method called for the initialization of the application.
*		auto Startup() -> void override
*		{
*			// Register my stages to the pipeline.
*			pipeline.AddStage<LogicStage>(...);
*			pipeline.AddStage<RenderingStage>();
*			pipeline.AddStage<GUIStage>();
*			pipeline.Startup(); // Remember to always call Startup to initialize the stages.
*		}
*		
*		// Method called for the shutdown of the application.
*		auto Shutdown() -> void override
*		{
*			// Save the state of the application if necessary.
*			
*			// Shutdown down the stages.
*			pipeline.Shutdown();
*		}
* 
*		
*		// Method called at the start of the every game loop before start.
*		auto Begin() -> void override
*		{
*			// Here we can do some checks or operations before the main Run method.
*		}
*		
*		auto End() -> void override
*		{
*			// Here we can do some checks or operations after the main Run method.
*		}
*		
*		auto Run() -> ApplicationState override
*		{
*			pipeline.Run();
*			
*			if (everything ok)
*			{
*				return ApplicationState::Running;
*			}
*			else // Something went wrong or the user closed the app, return exit to the engine.
*			{
*				return ApplicationState::Exit;
*			}
*		}
*	};
*	
*	engine.CreateApplication<MyApp>();
*	engine.Run();
* 
*/

export module gargantua.app.application;

import gargantua.app.pipeline;
import gargantua.app.stage;
import gargantua.time.time_step;

namespace gargantua::app
{
	export
	enum class ApplicationState
	{
		Running, // return this value if the application should continue running
		Close, // return this value if the application should be closed
	};

	export
	class Application
	{
	public:
		virtual ~Application() = default;
		
		// This function is called after the initialization of the engine systems.
		virtual auto Startup() -> void
		{
			
		}
		
		// This function is called before the shutdown of the engine systems.
		virtual auto Shutdown() -> void
		{
			
		}

		// Called every cycle before Run().
		virtual auto Begin() -> void
		{

		}

		// Called every cycle after Run().
		virtual auto End() -> void
		{

		}

		// Execute a step inside the application. This function is called inside the 
		// main loop between Begin and End.
		virtual auto Run(const time::TimeStep& ts) -> ApplicationState = 0;


		// Render ImGui.
		virtual auto RenderGUI() -> void
		{

		}

	protected:
		Pipeline pipeline;
	};
} // namespace gargantua::app