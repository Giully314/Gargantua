#pragma once
#include <cstdint>
#include <memory>
#include <utility>
#include <string>

//Define uniform types  to use across the engine.


namespace Gargantua
{
	using byte_t = std::uint8_t;

	using real_t = float;
	using natural_t = std::uint32_t;
	using integer_t = std::int32_t;

	using real64_t = double;
	using natural64_t = std::uint64_t;
	using integer64_t = std::int64_t;


	//************ INPUT ***************
	using key_t = std::uint16_t;
	using mouse_t = std::uint8_t;
	//**********************************


	//************ EVENT ***************
	using event_name_t = std::string;
	//**********************************


	/*
	Note on pointers: Resource should be handled only by these 3 types.
	"raw pointers" are accepted only with resource that are not handled by an object. (like references)
	*/

	//Unique resource owned.
	template <typename T>
	using UniqueRes = std::unique_ptr<T>;

	template <typename T, typename ...Args>
	constexpr UniqueRes<T> CreateUniqueRes(Args&& ...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	//Shared resource between multiple objects.
	template <typename T>
	using SharedRes = std::shared_ptr<T>;

	template <typename T, typename ...Args>
	constexpr SharedRes<T> CreateSharedRes(Args&& ...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}


	//Better to avoid use this for performance. 
	template <typename T>
	using WeakRes = std::weak_ptr<T>;


	//A simple pointer to a resource. The object using this MUST not perform construction or destruction
	//associated to this pointer.
	template <typename T>
	using NonOwnedRes = T*;


	//Inherite private from this class to disable copy (and get errors at compile time).
	struct NonCopyable
	{
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};


	struct NonMovable
	{
		NonMovable() = default;
		NonMovable(const NonMovable&) = delete;
		NonMovable& operator=(const NonMovable&) = delete;
	};
} //namespace Gargantua