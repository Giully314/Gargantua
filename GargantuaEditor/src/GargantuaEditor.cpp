/*
GargantuaEditor.cpp

OVERVIEW:
	Set the shaders to be used by the renderer2d.
	Set the stages of the pipeline.
*/

#include "GargantuaEditor.hpp"

#include "EditorDockingStage.hpp"
#include "EditorSceneStage.hpp"


namespace Gargantua
{
	namespace Editor
	{
		void GargantuaEditor::Start()
		{
			auto program = systems.shader_sys->CreateProgram("BasicTransform.vert", "BasicColorTexture.frag");
			auto fb_program = systems.shader_sys->CreateProgram("ScreenTransform.vert", "ScreenColor.frag");

			systems.renderer2d_sys->SetProgram(program);
			systems.renderer2d_sys->SetFBProgram(fb_program);

			pipeline.AddStage<EditorDockingStage>();
			pipeline.AddStage<EditorSceneStage>(systems);

			pipeline.Start();
		}


		void GargantuaEditor::Shutdown()
		{
			pipeline.End();
		}
	}
} 

