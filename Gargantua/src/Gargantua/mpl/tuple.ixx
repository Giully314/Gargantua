/*
* gargantua/mpl/tuple.ixx
* 
* PURPOSE: Functions on tuple.
* 
* DESCRIPTION:
*	https://www.fluentcpp.com/2019/03/08/stl-algorithms-on-tuples/
* 
* TODO: 
*	- Check with concepts the types.
*/

export module gargantua.mpl.tuple;

import <utility>;
import <initializer_list>;

import gargantua.types;

namespace gargantua::mpl
{
	template <typename TTuple, typename F, size_t ...I>
	constexpr auto ForEachImpl(TTuple&& t, F&& f, std::index_sequence<I...>) -> F
	{
		return (void)std::initializer_list<int>{(std::forward<F>(f)(std::get<I>(std::forward<TTuple>(t))), 0)...},
			f;
	}

	export 
	template <typename TTuple, typename F>
	constexpr auto ForEach(TTuple&& t, F&& f) -> F
	{
		return ForEachImpl(std::forward<TTuple>(t), std::forward<F>(f),
			std::make_index_sequence<std::tuple_size<std::remove_reference_t<TTuple>>::value>{});
	}



	export
	template <typename TTuple, typename TPredicate>
	constexpr auto FindIf(TTuple&& t, TPredicate predicate) -> u32
	{
		u32 idx = std::tuple_size<std::remove_reference_t<TTuple>>::value;
		u32 current_idx = 0;
		bool found = false;
		ForEach(t, [&](auto&& value)
			{
				if (!found && predicate(value))
				{
					idx = current_idx;
					found = true;
				}
				++current_idx;
			});
		return idx;
	}

	// Perform an action at given idx.
	export
	template <typename TTuple, typename TAction>
	constexpr auto Perform(TTuple&& t, u32 idx, TAction action) -> void
	{
		u32 current_idx = 0;
		ForEach(t, [action = std::move(action), idx, &current_idx](auto&& value)
			{
				if (current_idx == idx)
				{
					action(std::forward<decltype(value)>(value));
				}
				++current_idx;
			});
	}


	// Apply
	export
	template <typename TTuple>
	constexpr auto Min(TTuple&& t) -> u32
	{
		return 0;
	}
} // namespace gargantua::mpl
