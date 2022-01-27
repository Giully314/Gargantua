#pragma once

#include "Gargantua/Time/TimeStep.hpp"

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

			virtual ~Stage();


			/*
			Start the stage. Execute setup operations. Could be empty.
			*/
			virtual void Start() = 0;

			/*
			End the stage. Execute "save" operations. Could be empty.
			*/
			virtual void End() = 0;
			

			/*
			Execute the stage.
			*/
			virtual void Execute(const Time::TimeStep& ts) = 0;


			inline std::string_view GetName() const noexcept { return stage_name; }

		protected:
			const std::string stage_name;
		};
	} //namespace Core
} //namespace Gargantua