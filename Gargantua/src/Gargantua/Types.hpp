#pragma once
#include <cstdint>
#include <string_view>
#include <functional>
#include <memory>
#include <utility>
#include <source_location>

//Define uniform types  to use across the engine.


namespace Gargantua
{
	namespace Event
	{
		struct Event;
	}


	using real_t = float;
	using natural_t = std::uint32_t;
	using integer_t = std::int32_t;

	using real64_t = double;
	using natural64_t = std::uint64_t;
	using integer64_t = std::int64_t;


	////************ INPUT ***************
	using key_t = std::uint16_t;
	using mouse_t = std::uint8_t;
	////**********************************


	////************ EVENT ***************
	////USE ONLY INSIDE EVENT CLASS FOR EVENT NAME.
	//using event_name_t = std::string_view;
	//using event_callback = std::function<void(const Event::Event&)>;
	////**********************************



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
} //namespace Gargantua