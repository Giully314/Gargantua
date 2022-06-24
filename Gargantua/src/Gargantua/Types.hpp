#pragma once
/*
Gargantua/Types.hpp

PURPOSE: Define uniform types  to use across the engine.
*/

#include <glad/glad.h>


#include <cstdint>
#include <memory>
#include <utility>
#include <string>

namespace Gargantua
{
	using byte_t = std::uint8_t;

	using natural16_t = std::uint16_t;

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


	//************ RENDERER ************
	using render_id_t = GLuint;
	//**********************************



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