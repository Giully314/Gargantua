#include "Pipeline.hpp"

#include <algorithm>
#include <utility>


namespace Gargantua
{
	namespace Core
	{

		void Pipeline::AddStage(UniqueRes<Stage> stage)
		{
			const auto it = std::ranges::find_if(stages, [&](const UniqueRes<Stage>& s)
				{
					return stage->GetName() == s->GetName();
				});


			if (it == stages.end())
			{
				stages.push_back(std::move(stage));
			}
		}


		
		void Pipeline::AddStageAfter(UniqueRes<Stage> stage, std::string_view stage_name)
		{
			auto it = std::ranges::find_if(stages, [&](const UniqueRes<Stage>& s)
				{
					return stage_name == s->GetName();
				});

			if (it != stages.end())
			{
				//increment the iterator because the method insert, insert the element before the iterator.
				++it; 

				stages.insert(it, std::move(stage));
			}
		}


		void Pipeline::AddStageBefore(UniqueRes<Stage> stage, std::string_view stage_name)
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


		void Pipeline::RemoveStage(std::string_view stage_name)
		{
			stages.remove_if([=](const UniqueRes<Stage>& s)
				{
					return s->GetName() == stage_name;
				});
		}


		void Pipeline::Execute(const Time::TimeStep& ts)
		{
			std::ranges::for_each(stages, [&](UniqueRes<Stage>& s)
				{
					s->Start();
					s->Execute(ts);
					s->End();
				});
		}


		void Pipeline::RenderGUI()
		{
			std::ranges::for_each(stages, [&](UniqueRes<Stage>& s)
				{
					s->RenderGUI();
				});
		}

	} //namespace Core
} //namespace Gargantua