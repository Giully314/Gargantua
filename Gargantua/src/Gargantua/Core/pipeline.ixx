/*
gargantua/core/pipeline.ixx

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

	p.Execute(timestep);

	p.RenderGUI(); //For debug purpose, use a GUI to display the stage.


TODO:
	Make the pipeline parallel. This means that the user can specify if 2 or more stages can be
	executed in parallel. This allows more flexibility, performance for multithreading and
	decomposition of tasks.
*/

export module gargantua.core.pipeline;

import <concepts>;
import <string_view>;
import <list>;

import gargantua.core.stage;

import gargantua.types;

import gargantua.time.time_step;




namespace gargantua::core
{
	export class Pipeline
	{
	public:

		/*
		* Add a stage at the end of the pipeline.If the stage is already present, do nothing.
		*/
		auto AddStage(UniqueRes<Stage> s) -> void;

		template <typename T, typename ...Args>
			requires std::derived_from<T, Stage> and std::constructible_from<T, Args...>
		auto AddStage(Args&& ...args) -> void
		{
			AddStage(CreateUniqueRes<T>(std::forward<Args>(args)...));
		}


		/*
		* Add a stage after the specified stage.If the specified stage is not in the pipeline,
		* do nothing.
		*/
		auto AddStageAfter(UniqueRes<Stage> s, std::string_view stage_name) -> void;

		/*
		* Add a stage before the specified stage.If the specified stage is not in the pipeline,
		* do nothing.
		*/
		auto AddStageBefore(UniqueRes<Stage> s, std::string_view stage_name) -> void;

		/*
		* Remove the stage with the associated name.
		*/
		auto RemoveStage(std::string_view stage_name) -> void;


		/*
		* Start the pipeline calling the Start method for each stage. This method should be called before the
		* game loop. It is used for initializing the resources (once).
		*/
		auto Start() -> void;


		/*
		* End the pipeline calling the End method for each stage. This method should be called after the end of
		* the game loop for saving the state of a stage or deallocate resources.
		*/
		auto End() -> void;


		/*
		* Execute the pipeline. Call the Execute method for each stage.
		*/
		auto Execute(const time::TimeStep& ts) -> void;

		/*
		* Call RenderGUI for every stage.
		*/
		auto RenderGUI() -> void;


		//************** Iterators ************************
		
		auto begin() noexcept -> std::list<UniqueRes<Stage>>::iterator 
		{ 
			return stages.begin(); 
		}

		auto end() noexcept -> std::list<UniqueRes<Stage>>::iterator 
		{ 
			return stages.end(); 
		}


		auto cbegin() const noexcept -> std::list<UniqueRes<Stage>>::const_iterator 
		{ 
			return stages.cbegin(); 
		}


		auto cend() const noexcept -> std::list<UniqueRes<Stage>>::const_iterator 
		{ 
			return stages.cend(); 
		}

		//TODO: add views and filters

	private:
		std::list<UniqueRes<Stage>> stages;
	}; //class Pipeline

} //namespace gargantua::core

