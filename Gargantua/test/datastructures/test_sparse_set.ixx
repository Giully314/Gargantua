export module gargantua.test.datastructures.test_sparse_set;

import gargantua.test.test_base;

import gargantua.datastructures.sparse_set;

export namespace gargantua::test
{
	class TestSparseSet : public TestBase
	{
	public:
		auto RunTest() -> void override
		{
			logger.Debug("RunTest");
			constexpr auto n = 1000u;
			for (unsigned int i = 0; i < n; ++i)
			{
				logger.Debug("Inserting {}", i);
				s.insert(i);
			}
			
			logger.Debug("After insert");

			logger.Debug("{} is in the set: {}", 23, s.contains(23));
			logger.Debug("{} is in the set: {}", 2, s.contains(2));
			logger.Debug("{} is in the set: {}", 0, s.contains(0));
			logger.Debug("{} is in the set: {}", 1000, s.contains(1000));
			logger.Debug("{} is in the set: {}", 1001, s.contains(1001));
			

			for (auto i : s)
			{
				logger.Debug("{} is in the set", i);
			}


			logger.Debug("Erase all the elements");
			for (unsigned int i = 0; i < n; ++i)
			{
				//logger.Debug("Erasing {}", i);
				s.erase(i);
			}

			for (auto i : s)
			{
				logger.Debug("{} is in the set", i);
			}

			logger.Debug("{} is in the set: {}", 23, s.contains(23));
			logger.Debug("{} is in the set: {}", 2, s.contains(2));
			logger.Debug("{} is in the set: {}", 0, s.contains(0));
			logger.Debug("{} is in the set: {}", 1000, s.contains(1000));
			logger.Debug("{} is in the set: {}", 1001, s.contains(1001));
		}

	private:
		datastructures::SparseSet<unsigned int> s;
	};

} //namespace gargantua::test