/*
gargantua/core/application.cpp
*/

module gargantua.core.application;


namespace gargantua::core
{

	auto Application::Execute(const time::TimeStep& ts) -> void
	{
		pipeline.Execute(ts);
	}


	auto Application::RenderGUI() -> void
	{
		pipeline.RenderGUI();
	}
} //namespace gargantua::core
