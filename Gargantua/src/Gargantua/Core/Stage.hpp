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

TODO: add something to allow the stages to communicate?

*/

#include "Gargantua/Time/TimeStep.hpp"
#include "Gargantua/Event/EventRegisterManager.hpp"
#include "Gargantua/Event/EventListenerManager.hpp"
#include "Gargantua/Types.hpp"

#include <string>

namespace Gargantua
{
	namespace Core
	{
		/*
		A stage is a basic building block for creating a pipeline of operations to be executed.
		For example there could be a MotionStage, CollisionResolverStage and so on.

		TODO: consider to implement in the interface a function Save, that saves the state of the stage.
		*/
		class Stage
		{
		public:
			Stage(std::string stage_name_);

			Stage(const Stage&) = delete;
			Stage& operator=(const Stage&) = delete;

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


			virtual void RegisterEvents(NonOwnedRes<Event::EventRegisterManager> event_reg_mng)
			{

			}


			virtual void ListenToEvents(NonOwnedRes<Event::EventListenerManager> event_list_mng)
			{

			}


			inline std::string_view GetName() const noexcept { return stage_name; }

		protected:
			const std::string stage_name;
		};
	} //namespace Core
} //namespace Gargantua