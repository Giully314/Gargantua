/*
gargantua/app/pipeline.cpp
*/

module gargantua.app.pipeline;

import <algorithm>;
import <utility>;
import <string>;

namespace gargantua::app
{

	auto Pipeline::AddStage(unique_res<Stage> stage) -> void
	{
		auto it = std::ranges::find_if(stages, [&](const unique_res<Stage>& s)
			{
				return stage->GetName() == s->GetName();
			});


		if (it == stages.end()) [[likely]]
		{
			stages.push_back(std::move(stage));
		}
	}



	auto Pipeline::AddStageAfter(unique_res<Stage> stage, std::string_view stage_name) -> void
	{
		auto it = std::ranges::find_if(stages, [&](const unique_res<Stage>& s)
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


	auto Pipeline::AddStageBefore(unique_res<Stage> stage, std::string_view stage_name) -> void
	{
		auto it = std::ranges::find_if(stages, [&](const unique_res<Stage>& s)
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
		stages.remove_if([=](const unique_res<Stage>& s)
			{
				return s->GetName() == stage_name;
			});
	}


	auto Pipeline::Startup() -> void
	{
		std::ranges::for_each(stages, [](unique_res<Stage>& s)
			{
				s->Startup();
			});
	}


	auto Pipeline::Shutdown() -> void
	{
		std::ranges::for_each(stages, [](unique_res<Stage>& s)
			{
				s->Shutdown();
			});
	}


	auto Pipeline::Run(const time::TimeStep& ts) -> void
	{
		std::ranges::for_each(stages, [&](unique_res<Stage>& s)
			{
				s->Run(ts);
			});
	}


	auto Pipeline::RenderGUI() -> void
	{
		std::ranges::for_each(stages, [](unique_res<Stage>& s)
			{
				s->RenderGUI();
			});
	}

} // namespace gargantua::app