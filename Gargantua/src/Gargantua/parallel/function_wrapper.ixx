export module gargantua.parallel.thread_pool:function_wrapper;

import <concepts>;
import <utility>;

import gargantua.types;

namespace gargantua::parallel
{
	class FunctionWrapper
	{
	public:
		FunctionWrapper() = default;

		template <std::invocable F>
		FunctionWrapper(F&& f_) : f(CreateUniqueRes<Function<F>>(std::move(f_)))
		{

		}


		FunctionWrapper(const FunctionWrapper&) = delete;
		auto operator=(const FunctionWrapper&)->FunctionWrapper & = delete;

		FunctionWrapper(FunctionWrapper&& other) : f(std::move(other.f))
		{

		}


		auto operator=(FunctionWrapper&& other) -> FunctionWrapper&
		{
			f = std::move(other.f);
			return *this;
		}


		auto operator()() -> void
		{
			f->Call();
		}


	private:
		struct BaseFunction
		{
			virtual ~BaseFunction() = default;
			virtual auto Call() -> void = 0;
		};


		template <std::invocable F>
		struct Function : public BaseFunction
		{
			Function(F&& f_) : f(std::move(f_))
			{

			}

			auto Call() -> void override
			{
				f();
			}
		private:
			F f;
		};

	private:
		UniqueRes<BaseFunction> f;
	};
} //namespace gargantua::parallel