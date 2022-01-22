#pragma once

#include "../GargantuaTest.hpp"


#include "Gargantua/Core/TaskSystem.hpp"
#include <iostream>

namespace Gargantua
{
	namespace Test
	{
		class TestTaskSystem final : public GargantuaTest
		{
		public:
			void Create() override
			{
				Core::TaskSystem::Instance();
			}

			void Destroy() override 
			{

			}


			void RunTest() override
			{
				constexpr int n = 30;
				std::vector<int> v(n);

				for (int i = 0; i < n; ++i)
				{
					Core::TaskSystem::Instance()->AddLambda([](int* z, int j) 
						{
							*z += j;
						}, 
						&v[i], int{i});
				}

				std::cout << "Wait for all tasks" << std::endl;

				Core::TaskSystem::Instance()->WaitForAllTasks();

				for (const auto& i : v)
				{
					std::cout << i << "\n";
				}
			}

		};
	}
}