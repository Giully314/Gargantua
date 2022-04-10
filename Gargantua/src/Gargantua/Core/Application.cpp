/*
Gargantua/Core/Application.cpp
*/
#include "Application.hpp"


namespace Gargantua
{
	namespace Core
	{
		void Application::Execute(const Time::TimeStep& ts)
		{
			pipeline.Execute(ts);
		}


		void Application::RenderGUI()
		{
			pipeline.RenderGUI();
		}

	} //namespace Core
} //namespace Gargantua
