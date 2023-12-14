/*
* gargantuatest/math/test_vector.ixx
*/

export module gargantuatest.math.test_vector;

import <cassert>;

import gargantuatest.testbase;
import gargantua.math.vector;

export namespace gargantuatest
{
	class TestVector : TestBase
	{
	public:
		auto RunTest() -> void
		{
			using namespace gargantua::math;
			auto t = ConsoleLogTester("TestVector");
			
			{
				auto l = ConsoleLogTester("Vec2di");
				Vec2di xi{ 1, 4 };
				Vec2di yi{ 3, 2 };
				
				assert((xi + yi == Vec2di{ 4, 6 }));
				assert((xi * 3 == Vec2di{ 3, 12 }));
				assert((yi * 4 / 2 == Vec2di{ 6, 4 }));
			}
		}
	};
} // namespace gargantuatest