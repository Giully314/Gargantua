/*
Sandbox/src/Stages.cpp
*/
#include "Stages.hpp"

#include <Gargantua/Systems/ResourceSystem.hpp>

#include <Gargantua/Event/WindowEvents.hpp>
#include <Gargantua/Event/MouseEvents.hpp>

#include <Gargantua/Renderer/RendererCommand.hpp>


#include <imgui.h>


namespace Sandbox
{
	void RenderTestStage::Start() 
	{
		const real_t aspect_ratio = 1280.0f / 720.0f;
		controller.CreateCamera(aspect_ratio);

		auto& s = systems.engine_event_sys;
		s->GetEventListenerManager()->RegisterListener<Event::WindowResizeEvent>(
			[this](const Event::BaseEvent& e)
			{
				const Event::WindowResizeEvent& we = static_cast<const Event::WindowResizeEvent&>(e);
				controller.CreateCamera((real_t)we.new_width / (real_t)we.new_height);
			});	


		s->GetEventListenerManager()->RegisterListener<Event::MouseWheelScrollEvent>(
			[this](const Event::BaseEvent& e)
			{
				const Event::MouseWheelScrollEvent& me = static_cast<const Event::MouseWheelScrollEvent&>(e);
				
				controller.ZoomLevelOffset(me.y_offset);
			}
		);


		player.color = { 1, 0, 1, 1 };

		player2.position.x = 5;
		player2.color = { 0, 1, 0, 1 };

		background.position = { -1, -1 };
		background.scale = { 25, 15 };

		background.texture = Systems::ResourceSystem::LoadSharedTexture2d("resources/test/BG.png");
	}



	void RenderTestStage::Execute(const Time::TimeStep& ts) 
	{
		controller.Update(ts);
		systems.renderer2d_sys->BeginScene(controller.GetCamera());

		systems.renderer2d_sys->DrawQuad(background.position, background.scale, *background.texture);
		systems.renderer2d_sys->DrawQuad(player.position, player.scale, player.color);
		systems.renderer2d_sys->DrawQuad(player2.position, player2.scale, player2.color);

		systems.renderer2d_sys->EndScene();
        Renderer::RendererCommand::Clear();
        
	}


	void RenderTestStage::RenderGUI()
	{
       
	}
}