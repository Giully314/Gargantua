#pragma once
/*
GargantuaEditor.hpp

PURPOSE: Game editor using Gargantua.

CLASSES:
	GargantuaEditor: Application for the game editor.

DESCRIPTION:
	Initialize all the resources for the editor and register the stages of the pipeline.

*/

#include <Gargantua/Core/Application.hpp>
#include <Gargantua/Core/Stage.hpp>


namespace Gargantua
{
	namespace Editor
	{
		class GargantuaEditor : public Core::Application
		{
		public:
			// Inherited via Application
			virtual void Start() override;
			virtual void Shutdown() override;
		};



		inline GargantuaEditor* CreateGargantuaEditorApplication()
		{
			return new GargantuaEditor();
		}

	} //namespace Editor
} //namespace Gargantua