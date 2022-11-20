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
			s.Emplace(23, 3);
			s.Erase(23);
		}

	private:
		datastructures::SparseSet<size_t, int> s;
	};

} //namespace gargantua::test