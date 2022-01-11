#pragma once

namespace Gargantua
{
	namespace Core
	{
		/*
		Interface for the creation of an Application.
		*/
		class Application
		{
		public:
			Application() = default;

			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;

			Application(Application&&) = delete;
			Application& operator=(Application&&) = delete;

			virtual ~Application() = default;

			/*
			Execute should perform a single "tick" of the app.
			*/
			virtual void Execute(/*This function takes a TimeStep data*/) = 0;
		};


	} //namespace Core
} //namespace Gargantua