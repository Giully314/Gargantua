/*
* gargantua/mpl/mpl_typelist.ixx
* 
* PURPOSE: small metaprogramming library.
* 
* CLASSES:
* 	TypeList: a list of types.
* 	Rebind: rebind a list of types to another type (for example from TypeList to tuple.
* 	Transform: Apply a metafunction to every type in the list.
*	CheckPredicate: Check if a predicate is satisfied for every type in the list.
*	IsPresent: Check if a type is present in the list.
* 
* TODO:
* 	Concepts for the meta functions and predicates?
* 
* 
*/

export module gargantua.mpl.typelist;

import <type_traits>;
import <functional>;

export namespace gargantua::mpl
{

	template <typename ...TTypes>
	struct TypeList {};




	//************************ TRANSFORM ****************************************

	template <typename TList, template <class T> typename TMetaFunction>
	struct Transform;

	template <typename ...TTypes, template <class T> typename TMetaFunction>
	struct Transform<TypeList<TTypes...>, TMetaFunction>
	{
		using Type = TypeList<typename TMetaFunction<TTypes>::Type...>;
	};


	template <typename TList, template <class T> typename TMetaFunction>
	using TransformT = typename Transform<TList, TMetaFunction>::Type;

	//************************ TRANSFORM ****************************************



	//************************ EQUAL ********************************************
	template <typename TList1, typename TList2>
	struct AreEqual;

	template <typename ...Args1, typename ...Args2>
	struct AreEqual<TypeList<Args1...>, TypeList<Args2...>>
	{
		inline static constexpr bool value = (sizeof...(Args1) == sizeof...(Args2)) && 
			(std::is_same_v<Args1, Args2> && ...);
	};

	template <typename TList1, typename TList2>
	inline constexpr bool AreEqualV = AreEqual<TList1, TList2>::value;

	//************************ CHECK PREDICATE **********************************

	template <typename TList, template <class> typename TPredicate>
	struct CheckPredicate;

	template <typename ...TTypes, template <class> typename TPredicate>
	struct CheckPredicate<TypeList<TTypes...>, TPredicate>
	{
		static constexpr bool Value = (TPredicate<TTypes>::Value && ...);
	};


	template <typename TList, template <class> typename TPredicate>
	inline constexpr bool CheckPredicateV = CheckPredicate<TList, TPredicate>::Value;

	//************************ CHECK PREDICATE **********************************



	//************************** IS PRESENT **************************************

	//Check if there is at least one TType inside the TList.

	template <typename TList, typename TType>
	struct IsPresent;

	template <typename ...TTypes, typename TType>
	struct IsPresent<TypeList<TTypes...>, TType>
	{
		static constexpr bool Value = (std::is_same_v<TTypes, TType> || ...);
	};

	template <typename TList, typename TType>
	inline constexpr bool IsPresentV = IsPresent<TList, TType>::Value;

	//************************** IS PRESENT **************************************





	//************************* REBIND ******************************************

	template <typename TFrom, template <class...> typename TTo>
	struct Rebind;

	template <template <class ...Args1> typename TFrom, typename ...TTypes, template <class ...Args2> typename TTo>
	struct Rebind<TFrom<TTypes...>, TTo>
	{
		using Type = TTo<TTypes...>;
	};

	template <typename TFrom, template <class...> typename TTo>
	using RebindT = typename Rebind<TFrom, TTo>::Type;

	//************************* REBIND ******************************************


	//************************* REMOVE CVREF ************************************
	
	template <typename TList>
	struct RemoveCVRef;

	template <typename ...TTypes>
	struct RemoveCVRef<TypeList<TTypes...>>
	{
		using Type = TypeList<std::remove_cvref_t<TTypes>...>;
	};

	template <typename TList>
	using RemoveCVRefT = typename RemoveCVRef<TList>::Type;

	//************************* REMOVE CVREF ************************************


	//************************* CALLABLE INFO *******************


	template <typename F>
	struct CallableInfo;

	template <typename Result, typename ...Args>
	struct CallableInfo<std::function<Result(Args...)>>
	{
		using ReturnType = Result;
		using Params = TypeList<Args...>;
	};


	template <typename F>
	struct ReturnTypeOfFunction
	{
		using FunctionType = decltype(std::function{ std::declval<F>() });
		using Type = typename CallableInfo<FunctionType>::ReturnType;
	};

	template <typename F>
	using ReturnTypeOfFunctionT = typename ReturnTypeOfFunction<F>::Type;


	template <typename F>
	struct ParamsOfFunction
	{
		using FunctionType = decltype(std::function{ std::declval<F>() });
		using Type = typename CallableInfo<FunctionType>::Params;
	};

	template <typename F>
	using ParamsOfFunctionT = typename ParamsOfFunction<F>::Type;
	//************************* CALLABLE INFO *******************

} //namespace gargantua::mpl
