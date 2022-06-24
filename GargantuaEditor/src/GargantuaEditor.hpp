#pragma once
/*
GargantuaEditor.hpp


PURPOSE:

CLASSES:

DESCRIPTION:


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