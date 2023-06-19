/*
* editor/editor_camera.cpp
*/

module gargantua.editor.editor_camera;


namespace gargantua::editor
{
	auto EditorCamera::Run(const time::TimeStep& ts) -> void
	{
		using namespace platform;
		using namespace render;
		auto& inp = InputSystem::Instance();
		auto& t = camera.Get<TransformComponent>();
		auto& pos = t.position;
		auto& rot = t.rotation;
		auto upd = velocity * static_cast<f32>(ts.GetInSec());


		if (inp.IsPressed(Key::W))
		{
			pos.y += upd;
		}
		if (inp.IsPressed(Key::A))
		{
			pos.x -= upd;
		}
		if (inp.IsPressed(Key::S))
		{
			pos.y -= upd;
		}
		if (inp.IsPressed(Key::D))
		{
			pos.x += upd;
		}


		if (inp.IsPressed(Key::RIGHT))
		{
			rot -= upd;
		}
		if (inp.IsPressed(Key::LEFT))
		{
			rot += upd;
		}
	}
} // namespace gargantua::editor
