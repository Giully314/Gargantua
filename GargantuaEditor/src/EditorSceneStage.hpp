#pragma once
/*
EditorSceneStage.hpp


PURPOSE:


CLASSES:

DESCRIPTION:

*/

#include <imgui.h>

#include <Gargantua/Types.hpp>

#include <Gargantua/Core/Stage.hpp>
#include <Gargantua/Core/EngineSystems.hpp>

#include <Gargantua/Time/TimeStep.hpp>

#include <Gargantua/Renderer/OrthoCamera.hpp>
#include <Gargantua/Renderer/OrthoCameraController.hpp>

#include <Gargantua/Math/Vec2d.hpp>
#include <Gargantua/Math/Vec4d.hpp>



namespace Gargantua
{
	namespace Editor
	{
		//Temporary
		struct Quad
		{
			Math::Vec2df position;
			Math::Vec2df scale{ 1, 1 };

			real_t rotation = 0.0f;

			Math::Vec4df color{ 1, 1, 1, 1 };

			SharedRes<Renderer::Texture2d> texture;
		};



		class EditorSceneStage : public Core::Stage
		{
		public:
			EditorSceneStage(Core::EngineSystems systems_) : Stage("EditorSceneStage"), systems(std::move(systems_))
			{

			}


			// Inherited via Stage
			virtual void Start() override;
			virtual void End() override;
			virtual void Execute(const Time::TimeStep& ts) override;
			virtual void RenderGUI() override;



		private:
			Core::EngineSystems systems;
			
			Math::Vec2di scene_panel_size;
			

			UniqueRes<Renderer::OrthoCamera> ortho_cam;
			Renderer::OrthoCameraController controller;

			Quad player;
			Quad player2;
			Quad background;
		};
	}
}