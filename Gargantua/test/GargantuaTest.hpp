#pragma once


namespace Gargantua
{
	namespace Test
	{
		/*
		TODO: Make this class to automate some general test setup (maybe profiler, timing ecc).
		*/
		class GargantuaTest
		{
		public:
			virtual ~GargantuaTest() = default;
			virtual void Create()
			{

			}
			virtual void Destroy()
			{

			}
			virtual void RunTest() = 0;
		};

	} //namespace Test
} //namespace Gargantua