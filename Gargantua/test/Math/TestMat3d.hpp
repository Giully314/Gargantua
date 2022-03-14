#pragma once

#include "../GargantuaTest.hpp"

#include "Gargantua/Math/Mat3d.hpp"
#include "Gargantua/Math/Vec3d.hpp"
#include <iostream>


namespace Gargantua
{
	namespace Test
	{
		class TestMat3d : public GargantuaTest
		{
		public:

			void RunTest() override
			{
				using namespace Math;

				Vec3df v0{ 1, 2, 3};
				Vec3df v1{ 7, 9, 1};
				Vec3df v2{ 3, 17, 11};

				Mat3df m1{ v0, v1, v2};

				if (m1.Determinant() == 210)
				{
					std::cout << "LET'S GO" << std::endl;
				}

				std::cout << m1.Inverse().ToString() << std::endl;
				
			}
		};
	}
}
