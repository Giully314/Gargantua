#pragma once

#include "../GargantuaTest.hpp"

#include "Gargantua/Math/Mat2d.hpp"
#include "Gargantua/Math/Vec2d.hpp"
#include <iostream>


namespace Gargantua
{
	namespace Test
	{
		class TestMat2d : public GargantuaTest
		{
		public:

			void RunTest() override
			{
				Math::Mat2df m1{ 1, 2, 3, 4 };
				Math::Mat2df m2;
				m2.Identity();
				Math::Vec2df v1{ 2, 2 };

				auto m3 = m1 + m2;
				auto v2 = m1 * m2 * v1;

				std::cout << m3.ToString() << std::endl;
				std::cout << v2.ToString() << std::endl;
				std::cout << m1.Inverse().ToString() << std::endl;
			}
		};
	}
}