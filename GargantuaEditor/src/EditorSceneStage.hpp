#pragma once
/*
EditorSceneStage.hpp


PURPOSE: Edit scene of the game.

CLASSES:
	EditorSceneStage: Handle the scene using Dear ImGui.

DESCRIPTION:
	The aim of this editor should be to make it easy to develop game using the engine.
	Creation of the entities, components, systems, load resources and so on should be handled using 
	the gui with zero code from the user side. 
	In the future i would like to add scripting but for now i'm making the thing easy.
*/

#include <imgui.h>

#include <Gargantua/Types.hpp>

#include <Gargantua/Core/Stage.hpp>
#include <Gargantua/Core/EngineSystems.hpp>
#include <Gargantua/Core/Scene2d.hpp>


#include <Gargantua/Time/TimeStep.hpp>

#include <Gargantua/Math/Vec2d.hpp>
#include <Gargantua/Math/Vec4d.hpp>


#include "Gargantua/ECS/Types.hpp"

#include <vector>



namespace Gargantua
{
	namespace Editor
	{
		class EditorSceneStage : public Core::Stage
		{
		public:
			EditorSceneStage(Core::EngineSystems systems_) : Stage("EditorSceneStage"), systems(std::move(systems_))
			{
				scene = CreateSharedRes<Core::Scene2d>();
				scene->SetRenderer2d(systems.renderer2d_sys);
			}


			// Inherited via Stage
			virtual void Start() override;
			virtual void End() override;
			virtual void Execute(const Time::TimeStep& ts) override;
			virtual void RenderGUI() override;


		private:
			void RegisterEventListeners();



		private:
			Core::EngineSystems systems;

			SharedRes<Core::Scene2d> scene;
			
			Math::Vec2di scene_panel_size;

			ECS::Entity e1;
			ECS::Entity e2;
			ECS::Entity ground;
			ECS::Entity camera;
		};
	}
}