#pragma once
/*
Gargantua/Core/Stage.hpp

PURPOSE: Basic building block of an Application.

CLASSES:
	Stage: Abstract class the defines the basic operations of a Stage in a Pipeline.


DESCRIPTION:
	Basic building block of an Application. A Stage is like a big function with an internal state 
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


TODO: 
	add something to allow the stages to communicate?
	consider to implement in the interface a function Save, that saves the state of the stage.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Systems/EventSystem.hpp"

#include <string>

namespace Gargantua
{
	namespace Core
	{
		class Stage : private NonCopyable
		{
		public:
			Stage() = default;
			Stage(std::string stage_name_);

			Stage(Stage&&) noexcept = default;
			Stage& operator=(Stage&&) noexcept = default;

			virtual ~Stage() = default;


			/*
			Start the stage. Execute setup operations. Could be empty.
			*/
			virtual void Start() = 0;

			/*
			End the stage. Execute "save" operations. Could be empty.
			*/
			virtual void End() = 0;
			

			/*
			Execute the stage. Update the internal state or execute "logic" operations.
			*/
			virtual void Execute(const Time::TimeStep& ts) = 0;

			/*
			Render into the GUI. (Like ImGui). Could be empty.
			NOTE: This function is not meant to be a render call. This function should be implemented
			only for GUI interface in development process.
			For the "real" rendering part, there should exists a RenderStage for example.
			*/
			virtual void RenderGUI() = 0;


			virtual void ListenAndRegisterEvents(SharedRes<Systems::EventSystem> event_sys)
			{

			}


			std::string_view GetName() const noexcept { return stage_name; }

		protected:
			const std::string stage_name{"DefaultStageName"};
		};
	} //namespace Core
} //namespace Gargantua