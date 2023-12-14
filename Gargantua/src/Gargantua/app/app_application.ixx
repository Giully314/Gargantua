/*
* gargantua/app/app_application.ixx
* 
* PURPOSE: Application executed by the engine.
* 
* CLASSES:
*	ApplicationState: enum used as return value from Run() to check if the application must continue or exit.
*	Application: Define the API of an application executed by the engine.
* 
* DESCRIPTION:
*	The Application class is an abstract class used to define the API used by 
*	the engine for the execution of an app. To start using this class, just override the Run method 
*	and implement the logic to be executed each timestep.
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
	export enum class ApplicationState
	{
		Running, // return this value if the application should continue running
		Close, // return this value if the application should be closed
	};

	export class Application
	{
	public:
		virtual ~Application() = default;
		
		/* 
		* This function is called once before the gameloop to initialize the application. It is safe 
		* to access engine systems inside this function because all the engine functionalities are guaranteed
		* to be initialized at this point.
		*/
		virtual auto Startup() -> void
		{
			// TODO: this function could return ApplicationState to check if the startup went well.
		}
		
		/*
		* This function is called after the gameloop exit to close the application in a safe way. It is safe
		* to access engine systems inside this function because all the engine functionalities are guaranteed
		* to still be functioning at this point.
		*/
		virtual auto Shutdown() -> void
		{
			
		}

		/*
		* Called at each timestep of the game loop before Run().
		*/
		virtual auto Begin() -> void
		{

		}

		/*
		* Called at each timestep of the game loop after Run().
		*/
		virtual auto End() -> void
		{

		}

		/*
		* Called at each timestep of the game loop. This function must be implemented by the user to
		* provide logic of the application. The time step passed is the time between each call or a fixed
		* timestep if the logic rate is fixed.
		*/
		virtual auto Run(const time::TimeStep& ts) -> ApplicationState = 0;


		/*
		* Render the GUI of the application at the end of the game loop, after End() is called. 
		* The GUI supported is ImGUI. Note that this is a different type of rendering unlike the 
		* renderer with opengl (used to render a scene of objects). 
		*/
		virtual auto RenderGUI() -> void
		{

		}

	protected:
		Pipeline pipeline;
	};
} // namespace gargantua::app