#pragma once

#include "../GargantuaTest.hpp"

#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Core/Application.hpp"
#include "Gargantua/Core/Stage.hpp"
#include "Gargantua/Time/TimeStep.hpp"

#include <chrono>

namespace Gargantua
{
	namespace Test
	{
		class TestStage final : public Core::Stage
		{
		public:
			TestStage() : Core::Stage("TestStage")
			{

			}

			void Start() override
			{
				GRG_CORE_DEBUG("Start {}", stage_name);
			}

			void End() override
			{
				GRG_CORE_DEBUG("End {}", stage_name);
			}


			void Execute(const Time::TimeStep& ts) override
			{
				GRG_CORE_DEBUG("Execute {}", stage_name);
			}
		};

		class MyApplication final : public Core::Application
		{
		public:
			void Start() override
			{
				pipeline.AddStage<TestStage>();
			}

			void Shutdown() override
			{

			}
			

			void Execute(const Time::TimeStep& ts) override
			{
				pipeline.Execute(ts);
			}
		};


		class TestApplication final : public GargantuaTest
		{
		public:

			void RunTest() override
			{
				auto ts = Time::TimeStep{ std::chrono::duration<double>(4) };
				my_app.Start();
				my_app.Execute(ts);
				my_app.Execute(ts);
				my_app.Shutdown();
			}

		private:
			MyApplication my_app;
		};

	}
}