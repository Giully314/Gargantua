#pragma once
#include "../GargantuaTest.hpp"

#include "Gargantua/Engine.hpp"
#include "Gargantua/Types.hpp"
#include "Gargantua/Core/Application.hpp"

namespace Gargantua
{
	namespace Test
	{

		class Sandbox : public Gargantua::Core::Application
		{
		public:
			void Start() override { }
			void Shutdown() override { }
			void Reset() override { }


			void Execute(const Gargantua::Time::TimeStep& ts) override
			{

			}
		};

		/*
		This class test the basic functionalities of the engine: event system, window, input, stopwatch.
		*/
		class TestBasicEngine final : public GargantuaTest
		{
		public:
			void Create() override
			{
				engine = CreateUniqueRes<Engine>([]() {return new Sandbox{}; });
			}

			void Destroy() override
			{
				engine.reset();
			}


			void RunTest() override
			{
				Create();


				engine->Run();


				Destroy();
			}



		private:
			UniqueRes<Engine> engine;
		};
	}
}