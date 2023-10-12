/*
* editor/scene_stage.cpp
*/
module;

#include <imgui.h>

#include <gargantua/log/logger_macro.hpp>

module gargantua.editor.scene_stage;


namespace gargantua::editor
{
	auto SceneStage::Startup() -> void
	{
		//ImVec2 view = ImGui::GetContentRegionAvail();
		context->SetViewport(1080, 720);
	}


	auto SceneStage::Run(const time::TimeStep& ts) -> void
	{
		//math::Vec2df position{ 0.0f, 0.0f };
		//math::Vec4df color{ 0.0f, 1.0f, 1.0f, 1.0f };
		//math::Vec2df size{ 1, 1 };
		//auto texture = render::TextureSystem::Instance().Get("WhiteTexture");

		//auto& renderer = render::Renderer2dSystem::Instance();
		////renderer.DrawRotatedQuad(position, size, 1.0f, texture);

		context->Run(ts);
		/*context->ECS().ForEach<physics::PositionComponent>(
			[&](const physics::PositionComponent& p)
			{
				GRG_CORE_INFO("{}", p.p.ToString());
			}
		);*/
	}

	auto SceneStage::RenderGUI() -> void
	{
		ImGui::Begin("Scene2d");

		// The imgui window has size 0.
		if (!HandleWindowResize())
		{ 
			ImGui::End();
			return;
		}

		auto& renderer = render::Renderer2dSystem::Instance();
		unsigned int fbid = renderer.GetFrameBuffer().GetBufferId();
		auto& fb = renderer.GetFrameBuffer();
		ImGui::Image((void*)fbid, { (float)fb.GetWidth(), (float)fb.GetHeight() }, 
			ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
	}


	auto SceneStage::HandleWindowResize() -> bool
	{
		ImVec2 view = ImGui::GetContentRegionAvail();
		auto scene_view = context->GetViewport();


		if (view.x != scene_view.x || view.y != scene_view.y)
		{
			if (view.x == 0 || view.y == 0)
			{
				// The window is too small or collapsed.
				return false;
			}

			u32 new_width = static_cast<u32>(view.x);
			u32 new_height = static_cast<u32>(view.y);
			context->SetViewport(new_width, new_height);
			render::Renderer2dSystem::Instance().Resize(new_width, new_height);

			// The window state has been successfully changed.
			return true;
		}

		// The window state has not changed.
		return true;
	}

} // namespace gargantua::editor
