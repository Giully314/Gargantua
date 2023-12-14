/*
gargantua/app/app_pipeline.ixx

PURPOSE: Simulate a pipeline of execution.

CLASSES:
	Pipeline: Manages the stages to be executed in a specific order.


DESCRIPTION:
	This class simulate a pipeline of stages to be executed inside the Application class.
	The purpose of this approach is to allow the user to decompose the Application into different
	stages and focus only on one thing at time.


USAGE:
	Pipeline p;

	p.AddStage<PhysicStage>(parameters);
	p.AddStage<AnimationStage>(parameters);

	p.Startup(); // Calls Startup() for every stage in order.
	
	p.Execute(timestep);

	p.RenderGUI(); //For debug purpose, use a GUI to display the stage.

	
	// At the end of the program.
	p.Shutdown(); // Can be used to save the state of the stages.

TODO:
	Make the pipeline parallel. This means that the user can specify if 2 or more stages can be
	executed in parallel. This allows more flexibility, performance for multithreading and
	decomposition of tasks.
*/

export module gargantua.app.pipeline;

import <concepts>;
import <string_view>;
import <vector>;


import gargantua.types;
import gargantua.app.stage;
import gargantua.time.time_step;


namespace gargantua::app
{
	export class Pipeline
	{
	public:

		/*
		* Add a stage at the end of the pipeline. If the stage is already present, do nothing.
		*/
		auto AppendStage(unique_res<Stage> s) -> void;

		template <typename T, typename ...Args>
			requires std::derived_from<T, Stage> && std::constructible_from<T, Args...>
		auto AppendStage(Args&& ...args) -> void
		{
			AppendStage(CreateUniqueRes<T>(std::forward<Args>(args)...));
		}

		/*
		* Remove the stage with the associated name.
		*/
		auto RemoveStage(const std::string_view stage_name) -> void;


		/*
		* Start the pipeline calling the Start method for each stage. This method should be called before the
		* game loop. It is used for initializing the resources (once).
		*/
		auto Startup() -> void;


		/*
		* End the pipeline calling the End method for each stage. This method should be called after the end of
		* the game loop for saving the state of a stage or deallocate resources.
		*/
		auto Shutdown() -> void;


		/*
		* Execute the pipeline. Call the Execute method for each stage.
		*/
		auto Run(const time::TimeStep& ts) -> void;

		/*
		* Call RenderGUI for every stage.
		*/
		auto RenderGUI() -> void;


		//************** Iterators ************************

		auto begin() noexcept -> std::vector<unique_res<Stage>>::iterator
		{
			return stages.begin();
		}

		auto end() noexcept -> std::vector<unique_res<Stage>>::iterator
		{
			return stages.end();
		}


		auto begin() const noexcept -> std::vector<unique_res<Stage>>::const_iterator
		{
			return stages.cbegin();
		}


		auto end() const noexcept -> std::vector<unique_res<Stage>>::const_iterator
		{
			return stages.cend();
		}


		auto cbegin() const noexcept -> std::vector<unique_res<Stage>>::const_iterator
		{
			return stages.cbegin();
		}


		auto cend() const noexcept -> std::vector<unique_res<Stage>>::const_iterator
		{
			return stages.cend();
		}

		//TODO: add views and filters

	private:
		std::vector<unique_res<Stage>> stages;
	}; 

} //namespace gargantua::app

