/*
* gargantua/generator/coroutine_generator.ixx
* 
* PURPOSE: Generator class.
* 
* CLASSES:
*   Generator: a template coroutine generator. Based on std::generator (available in c++23).
* 
* DESCRIPTION:
*   Based on: 
*       - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2502r2.pdf
*       - https://en.cppreference.com/w/cpp/language/coroutines
*       - https://github.com/jbaldwin/libcoro/blob/main/inc/coro/generator.hpp (just used as comparison).
* 
* TODO:
*   - Make it more STL oriented. typedefs, handling exception and so on.
*/

export module gargantua.generator.coroutine_generator;

import <concepts>;
import <coroutine>;
import <utility>;
import <memory>;


export namespace gargantua::generator
{
	template <typename T>
	concept GeneratorTypeC = std::default_initializable<T> && std::movable<T>;

	template <GeneratorTypeC T>
	class Generator;



    template <GeneratorTypeC T>
    class GeneratorPromise
    {
    public:
        Generator<T> get_return_object() noexcept;

        std::suspend_always initial_suspend() noexcept
        {
            return {};
        }

        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        std::suspend_always yield_value(std::remove_reference_t<T>& value_) noexcept
        {
            this->value_ = std::addressof(value_);
            return {};
        }

        void return_void()
        {

        }

        void unhandled_exception()
        {

        }

        T& value()
        {
            return *value_;
        }

    private:
        // WE can use a pointer to the value, because the value lifetime crosses the suspension point inside the co_yield
        T* value_{};
    };




    struct GeneratorSentinel {};

    template <typename T>
    class GeneratorIterator
    {
    public:
        using Handle = std::coroutine_handle<GeneratorPromise<T>>;


        friend auto operator==(const GeneratorIterator& it, GeneratorSentinel) noexcept -> bool
        {
            return it.coro_hdl == nullptr || it.coro_hdl.done();
        }

        friend auto operator!=(const GeneratorIterator& it, GeneratorSentinel s) noexcept -> bool { return !(it == s); }

        friend auto operator==(GeneratorSentinel s, const GeneratorIterator& it) noexcept -> bool { return (it == s); }

        friend auto operator!=(GeneratorSentinel s, const GeneratorIterator& it) noexcept -> bool { return it != s; }


        GeneratorIterator() noexcept { }
        explicit GeneratorIterator(Handle hdl) noexcept : coro_hdl{ hdl }
        {

        }

        GeneratorIterator& operator++()
        {
            coro_hdl.resume();
            if (coro_hdl.done())
            {
                // coro_hdl.promise().rethrow_if_exception();
            }

            return *this;
        }

        auto operator++(int) -> void { (void)operator++(); }


        T& operator*() const noexcept { return coro_hdl.promise().value(); }

        T* operator->() const noexcept { return std::addressof(operator*()); }
    
    private:
        Handle coro_hdl{ nullptr };
    };




	template <GeneratorTypeC T>
	class Generator
	{
    public:
        using promise_type = GeneratorPromise<T>;

        explicit Generator(promise_type* p) : coro_hdl{ Handle::from_promise(*p) }
        {

        }

        Generator(Generator&& rhs) noexcept(noexcept(std::exchange(rhs.coro_hdl, nullptr))) : 
            coro_hdl{std::exchange(rhs.coro_hdl, nullptr)}
        {

        }

        ~Generator()
        {
            if (coro_hdl)
            {
                coro_hdl.destroy();
            }
        }


        T& value()
        {
            return *coro_hdl.promise().value;
        }

        bool finished() const
        {
            return coro_hdl.done();
        }

        void resume()
        {
            if (not finished())
            {
                coro_hdl.resume();
            }
        }


        auto begin() -> GeneratorIterator<T>
        {
            if (coro_hdl != nullptr)
            {
                coro_hdl.resume();
                if (coro_hdl.done())
                {
                    // coro_hdl.promise().rethrow_if_exception();
                }
            }

            return GeneratorIterator<T>{coro_hdl};
        }

        auto end() noexcept -> GeneratorSentinel { return {}; }

    private:
        using Handle = std::coroutine_handle<promise_type>;
        Handle coro_hdl{};
	};



    template <GeneratorTypeC T>
    Generator<T> GeneratorPromise<T>::get_return_object() noexcept
    {
        return Generator<T>{this};
    }

} // namespace gargantua::generator
