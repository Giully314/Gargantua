#pragma once
/*
Gargantua/Core/Pipeline.hpp

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



#include "Gargantua/Types.hpp"

#include "Gargantua/Core/Stage.hpp"
#include "Gargantua/Time/TimeStep.hpp"

#include <concepts>
#include <string_view>
#include <list>



namespace Gargantua
{
	namespace Core
	{
		class Pipeline
		{
		public:

			//Add a stage at the end of the pipeline. If the stage is already present, do nothing.
			void AddStage(UniqueRes<Stage> s);

			template <typename T, typename ...Args>
			requires std::derived_from<T, Stage> && std::constructible_from<T, Args...>
			inline void AddStage(Args&& ...args)
			{
				AddStage(CreateUniqueRes<T>(std::forward<Args>(args)...));
			}


			/*
			Add a stage after the specified stage.If the specified stage is not in the pipeline,
			do nothing.
			*/
			void AddStageAfter(UniqueRes<Stage> s, std::string_view stage_name);

			/*
			Add a stage before the specified stage.If the specified stage is not in the pipeline,
			do nothing.
			*/
			void AddStageBefore(UniqueRes<Stage> s, std::string_view stage_name);

			/*
			Remove the stage with the associated name.
			*/
			void RemoveStage(std::string_view stage_name);

			/*
			Execute the pipeline. This means that for every stage, Start, Execute and End are called.
			*/
			void Execute(const Time::TimeStep& ts);

			/*
			Call RenderGUI for every stage.
			*/
			void RenderGUI();


			//************** Iterators ************************
			std::list<UniqueRes<Stage>>::iterator begin() noexcept { return stages.begin(); }
			std::list<UniqueRes<Stage>>::iterator end() noexcept { return stages.end(); }

			std::list<UniqueRes<Stage>>::const_iterator cbegin() const noexcept { return stages.cbegin(); }
			std::list<UniqueRes<Stage>>::const_iterator cend() const noexcept { return stages.cend(); }

			//TODO: add views and filters

		private:
			std::list<UniqueRes<Stage>> stages;
		};
	}
}