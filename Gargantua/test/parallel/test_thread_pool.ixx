/*
gargantua/test/test_thread_pool.ixx
*/

export module gargantua.test.parallel.test_thread_pool;

import <vector>;
import <unordered_map>;
import <future>;
import <thread>;

import gargantua.test.test_base;

import gargantua.parallel.thread_pool;

export namespace gargantua::test
{
	class TestThreadPool : public TestBase
	{
	public:
		TestThreadPool() : objs(100)
		{

		}

		auto RunTest() -> void override
		{
			logger.Debug("Ciao {}", 3);
			constexpr unsigned n = 100;
			for (unsigned i = 0; i < n; ++i)
			{
				//logger.Debug("creating {} thread", i);
				futures.emplace_back(pool.RegisterTrackedTask([&, i]()
					{
						mutex_logger.Debug("Thread id:");
						pool.RegisterTask([&, i]()
							{
								int x = 0;
								for (int j = 0; j < 100; ++j)
								{
									objs[i] += j;
								}
							});
					}));
			}

			for (auto& f : futures)
			{
				//logger.Debug("valid: {}", f.valid());
				f.wait();
			}

			for (auto x : objs)
			{
				logger.Debug("{}", x);
			}
		}

	private:
		parallel::ThreadPool pool;
		
		std::vector<std::future<void>> futures;
		std::vector<int> objs;
	};

} //namespace gargantua::test