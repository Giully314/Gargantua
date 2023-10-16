/*
gargantua/app/stage.ixx

PURPOSE: Basic building block of an Application.

CLASSES:
	Stage: Abstract class the defines the basic operations of a Stage in a Pipeline.


DESCRIPTION:
	Basic building block of an Application. A Stage is like a function with an internal state
	that does only one thing. For example, a RendererStage is a stage that uses the renderer system
	to draw the entities after the PhysicsStage has computed the physics.


USAGE:
	class MyLevelGameStage : public Stage
	{
		//implement the logic of a level.
	};


	Note: consider to implent a System in the ecs for the rendering instaed of a stage if it is only
	necessary to render entities.
	class MyRenderingStage : public Stage
	{
	};


	// Register the stages in the pipeline inside the Application.
	pipeline.AddStage<MyLevelGameStage>();
	pipeline.AddStage<MyRenderingStage>();


TODO:
	- add something to allow the stages to communicate?
	- consider to implement in the interface a function Save, that saves the state of the stage.
*/

export module gargantua.app.stage;

import <string>;
import <string_view>;

import gargantua.types;

import gargantua.time.time_step;



namespace gargantua::app
{
	export 
	class Stage
	{
	public:
		Stage() = default;

		Stage(std::string stage_name_) : stage_name(std::move(stage_name_))
		{

		}

		Stage(const Stage&) = delete;
		Stage& operator=(const Stage&) = delete;

		Stage(Stage&&) noexcept = default;
		Stage& operator=(Stage&&) noexcept = default;

		virtual ~Stage() = default;


		/*
		* Start the stage. Execute setup operations. Could be empty.
		*/
		virtual auto Startup() -> void
		{

		}

		/*
		* End the stage. Execute "save" operations. Could be empty.
		*/
		virtual auto Shutdown() -> void
		{

		}


		/*
		* Run the stage. Update the internal state or execute "logic" operations.
		*/
		virtual auto Run(const time::TimeStep& ts) -> void
		{

		}

		/*
		* Render into the GUI. (Like ImGui). Could be empty.
		* NOTE: This function is not meant to be a render call. This function should be implemented
		* only for GUI interface in development process.
		* For the "real" rendering part, there should exists a RenderStage for example.
		*/
		virtual auto RenderGUI() -> void
		{

		}

		/*
		* Get the name of the stage.
		*/
		auto GetName() const noexcept -> std::string_view
		{
			return stage_name;
		}

	protected:
		std::string stage_name{ "DefaultStageName" };
	}; 
} //namespace gargantua::app
