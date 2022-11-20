/*
gargantua/core/pipeline.cpp
*/

module gargantua.core.pipeline;

import <algorithm>;
import <utility>;
import <string>;

namespace gargantua::core
{

	auto Pipeline::AddStage(UniqueRes<Stage> stage) -> void
	{
		auto it = std::ranges::find_if(stages, [&](const UniqueRes<Stage>& s)
			{
				return stage->GetName() == s->GetName();
			});


		if (it == stages.end()) [[likely]]
		{
			stages.push_back(std::move(stage));
		}
	}



	auto Pipeline::AddStageAfter(UniqueRes<Stage> stage, std::string_view stage_name) -> void
	{
		auto it = std::ranges::find_if(stages, [&](const UniqueRes<Stage>& s)
			{
				return stage_name == s->GetName();
			});

		if (it != stages.end()) [[likely]]
		{
			//increment the iterator because the method insert, inserts the element before the iterator.
			++it;

			stages.insert(it, std::move(stage));
		}
	}


	auto Pipeline::AddStageBefore(UniqueRes<Stage> stage, std::string_view stage_name) -> void
	{
		auto it = std::ranges::find_if(stages, [&](const UniqueRes<Stage>& s)
			{
				return stage_name == s->GetName();
			});

		if (it != stages.end())
		{
			stages.insert(it, std::move(stage));
		}
	}


	auto Pipeline::RemoveStage(std::string_view stage_name) -> void
	{
		stages.remove_if([=](const UniqueRes<Stage>& s)
			{
				return s->GetName() == stage_name;
			});
	}


	auto Pipeline::Start() -> void
	{
		std::ranges::for_each(stages, [](UniqueRes<Stage>& s)
			{
				s->Start();
			});
	}


	auto Pipeline::End() -> void
	{
		std::ranges::for_each(stages, [](UniqueRes<Stage>& s)
			{
				s->End();
			});
	}


	auto Pipeline::Execute(const time::TimeStep& ts) -> void
	{
		std::ranges::for_each(stages, [&](UniqueRes<Stage>& s)
			{
				s->Execute(ts);
			});
	}


	auto Pipeline::RenderGUI() -> void
	{
		std::ranges::for_each(stages, [](UniqueRes<Stage>& s)
			{
				s->RenderGUI();
			});
	}

} //namespace gargantua::core