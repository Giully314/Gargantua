/*
gargantua/types.ixx

PURPOSE: Define uniform types  to use across the engine.
*/
module;

#include <glad/glad.h>

export module gargantua.types;

export import <memory>;
import <string>;
import <utility>;
import <cstdint>;

export namespace gargantua
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




	/*
	Make it a wrapper class that can be init from unique, shared and pointers
	but simply avoid to delete a pointer.
	*/
	template <typename T>
	using NonOwnedRes = T*;

	//This is just a type alias. Using this communicates that there is no check for nullptr.
	template <typename T>
	using NonNullableRes = T*;


	//Unique resource owned.
	template <typename T>
	using UniqueRes = std::unique_ptr<T>;

	template <typename T, typename ...Args>
	inline auto CreateUniqueRes(Args&& ...args) -> UniqueRes<T>
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	//Shared resource between multiple objects.
	template <typename T>
	using SharedRes = std::shared_ptr<T>;

	template <typename T, typename ...Args>
	inline auto CreateSharedRes(Args&& ...args) -> SharedRes<T>
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
} //namespace gargantua