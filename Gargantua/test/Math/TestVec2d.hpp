#pragma once

#include "../GargantuaTest.hpp"

#include "Gargantua/Math/Vec2d.hpp"

#include <iostream>

namespace Gargantua
{
	namespace Test
	{
		class TestVec2d : public GargantuaTest
		{
		public:
			void RunTest() override
			{
				using namespace Math;
				Vec2df v1{10, 12}, v2{1, 2};

				auto v3 = v1 + v2;
				auto v4 = v1 - v2;
				auto v5 = v1 * 5;

				std::cout << v3.ToString() << std::endl;
				std::cout << v4.ToString() << std::endl;
				std::cout << v5.ToString() << std::endl;
			}
			
		};

	} //namespace Test
} //namespace Gargantua