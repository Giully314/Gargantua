/*
gargantua/mpl/type_list.ixx


PURPOSE:

CLASSES:
	TypeList:
	Rebind:
	Transform:


DESCRIPTION:


TODO:
	Concepts for the meta functions and predicates?

USAGE:


*/

export module gargantua.mpl.type_list;

import <type_traits>;

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

} //namespace gargantua::mpl
