#pragma once

#include "../GargantuaTest.hpp"

#include "Gargantua/Math/Mat4d.hpp"
#include "Gargantua/Math/Vec4d.hpp"
#include <iostream>


namespace Gargantua
{
	namespace Test
	{
		class TestMat4d : public GargantuaTest
		{
		public:

			void RunTest() override
			{
				using namespace Math;

				Vec4di v0{ 2, 3, 1, 4 };
				Vec4di v1{ 0, 1, 5, 6 };
				Vec4di v2{ 7, 1, 2, 3 };
				Vec4di v3{ 4, 8, 8, 0 };
				
				Vec4di v4{ 1, 2, 3, 4 };
				Vec4di v5{ 5, 6, 7, 8 };
				Vec4di v6{ 1, 2, 9, 0 };
				Vec4di v7{ 1, 3, 4, 5 };

				Vec4di r0{ 22, 36, 52, 52 };
				Vec4di r1{ 16, 34, 76, 38 };
				Vec4di r2{ 17, 33, 58, 51 };
				Vec4di r3{ 52, 72, 140, 80 };

				Mat4di m1{v0, v1, v2, v3};
				Mat4di m2{v4, v5, v6, v7};
				Mat4di true_res{r0, r1, r2, r3};

				Mat4di res = m1 * m2;

				if (res == true_res)
				{
					std::cout << "LET'S GO prodotto giusto" << std::endl;
				}

				Vec4df i0{ 1, 2, 3, 4 };
				Vec4df i1{ 5, 6, 7, 8 };
				Vec4df i2{ 11, 17, 1, 3 };
				Vec4df i3{ 7, 0, 17, 5 };

				Mat4df m{ i0, i1, i2, i3 };

				if (m.Determinant() == -824)
				{
					std::cout << "Determinant right" << std::endl;
				}

				auto inv = m.Inverse();

				std::cout << inv.ToString() << std::endl;
			}
		};
	}
}