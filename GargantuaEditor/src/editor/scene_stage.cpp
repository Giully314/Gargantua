
module;

#include <imgui.h>

module gargantua.editor.scene_stage;


namespace gargantua::editor
{
	

	auto SceneStage::Run(const time::TimeStep& ts) -> void
	{
		math::Vec2df position{ 0.0f, 0.0f };
		math::Vec4df color{ 0.0f, 1.0f, 1.0f, 1.0f };
		math::Vec2df size{ 1, 1 };
		auto texture = render::TextureSystem::Instance().Get("WhiteTexture");

		auto& renderer = render::Renderer2dSystem::Instance();
		//renderer.DrawRotatedQuad(position, size, 1.0f, texture);

		context->Run(ts);
	}

	auto SceneStage::RenderGUI() -> void
	{
		ImGui::Begin("Scene2d");
		auto& renderer = render::Renderer2dSystem::Instance();
		unsigned int fbid = renderer.GetFrameBuffer().GetBufferId();
		auto& fb = renderer.GetFrameBuffer();
		ImGui::Image((void*)fbid, { (float)fb.GetWidth(), (float)fb.GetHeight() }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
	}

} // namespace gargantua::editor
