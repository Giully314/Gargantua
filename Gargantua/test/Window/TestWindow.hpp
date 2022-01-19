#pragma once

#include "Gargantua/Types.hpp"
#include "Gargantua/Core/Window.hpp"

namespace Gargantua
{
	namespace Test
	{
		class TestWindow
		{

		public:
			TestWindow() = default;
		
			void RunTest()
			{
				window = CreateUniqueRes<Core::Window>("Test", 480, 360);

				window->Update();
			}

		private:
			UniqueRes<Core::Window> window = nullptr; 
		};
	}
}