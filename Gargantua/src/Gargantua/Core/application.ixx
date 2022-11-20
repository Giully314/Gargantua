/*
gargantua/core/application.ixx

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

			...


			pipeline.Start();
		}


		void Shutdown() override
		{
			...

			pipeline.End();
		}
	}

	Gargantua::Engine e {[](){return new MyApplication();}, width, height};
*/

export module gargantua.core.application;

import gargantua.types;

import gargantua.time.time_step;

import gargantua.core.pipeline;

import gargantua.system.system;


namespace gargantua::core
{

	export struct EngineSystems
	{
		//TODO: are all these systems necessary from the engine side?
		//for example the app_event_sys and ecs_sys are "useless" in the engine class.
		//Even the renderer2d
		SharedRes<system::EventSystem> engine_event_sys;
		SharedRes<system::EventSystem> app_event_sys;
		SharedRes<system::Renderer2dSystem> renderer2d_sys;
		SharedRes<system::ShaderSystem> shader_sys;
		SharedRes<system::TimeSystem> time_sys;
	}; //struct Enginesystems


	export class Application 
	{
	public:
		Application() = default;

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		Application(Application&&) = default;
		Application& operator=(Application&&) = default;

		virtual ~Application() = default;


		/*
		* This function is called at the start of the Run method from Engine.
		* Note that this function doesn't replace the role of constructor.
		* This function could be used to initialize the stages, register listeners and events and so on.
		* After adding the stages to the pipeline, the Start method of the pipeline should be called for
		* the correcting initialization of the stages.
		*/
		virtual auto Start() -> void = 0;


		/*
		* This function is called at the end of the Run method from Engine.
		* Note that this function doesn't replace the role of destructor.
		* The End method of the pipeline should be called for the correct end of the stages.
		*/
		virtual auto Shutdown() -> void = 0;


		/*
		* Reset the application. Is safe to call this function before Shutdown?
		* Think about it. Maybe this method is useless.
		*/
		//virtual void Reset() = 0;


		/*
		* Loop through the pipeline and execute every stage.
		*/
		auto Execute(const time::TimeStep&) -> void;


		/*
		* Call RenderGUI for every stage. 
		* Note that this is not the same as rendering an object in the scene. 
		* Rendering the graphics user interface and rendering an object in the scene are 
		* two different things.
		*/
		auto RenderGUI() -> void;

		/*
		* Return the systems used by the application.
		*/
		auto GetEngineSystems() noexcept -> EngineSystems&
		{
			return systems;
		}


	protected:
		Pipeline pipeline;
		EngineSystems systems;
	};

} //namespace core
