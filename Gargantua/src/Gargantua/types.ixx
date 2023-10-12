/*
* gargantua/types.ixx
* 
* PURPOSE: 
*	Define uniform types  to use across the engine.
* 
*/
module;

#include <glad/glad.h>

export module gargantua.types;

export import <memory>;
import <concepts>;
import <type_traits>;
import <string>;
import <utility>;
import <cstdint>;

export namespace gargantua
{
	using u8 = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using i32 = std::int32_t;
	using i64 = std::int64_t;

	using f32 = float;
	using f64 = double;


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




	// Note: It must be guaranteed that the resource passed has a lifespan larger than the use.
	template <typename T>
	using non_owned_res = T*;
	

	////This is just a type alias. Using this communicates that there is no check for nullptr.
	//template <typename T>
	//using non_nullable_res = T*;

	//Unique resource owned.
	template <typename T>
	using unique_res = std::unique_ptr<T>;

	template <typename T, typename ...Args>
	inline auto CreateUniqueRes(Args&& ...args) -> unique_res<T>
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	//Shared resource between multiple objects.
	template <typename T>
	using shared_res = std::shared_ptr<T>;

	template <typename T, typename ...Args>
	inline auto CreateSharedRes(Args&& ...args) -> shared_res<T>
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	


	// Used to avoid boilerplate when converting enums to underlying type.
	// For example, given an element e of an enum MyEnum, we can access its value
	// as +e instaed of static_cast<bla bla>(e);
	// Trick from: Andrei Alexandrescu.
	// Note: in c++23 there is std::to_underlying, maybe it's better in terms of readability.
	template <typename Enum>
		requires std::is_enum_v<Enum>
	auto operator+(Enum e) -> std::underlying_type_t<Enum>
	{
		return static_cast<std::underlying_type_t<Enum>>(e);
	}


	//Inherite private from this class to disable copy (and get errors at compile time).
	struct NonCopyable
	{
		NonCopyable() = default;
		NonCopyable(NonCopyable&&) = default;
		NonCopyable& operator=(NonCopyable&&) = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;	
	};


	struct NonMovable
	{
		NonMovable() = default;
		NonMovable(NonMovable&&) = delete;
		NonMovable& operator=(NonMovable&&) = delete;
		NonMovable(const NonMovable&) = default;
		NonMovable& operator=(const NonMovable&) = default;
	};


	// TODO: refactor the singletons to make the constructors private.
	// Remove this after.
	template<std::default_initializable T>
	//template<typename T>
	class Singleton : private NonCopyable, private NonMovable
	{
	protected:
		Singleton() = default;
	
	public:
		static auto Instance() -> T&
		{
			static T instance;
			return instance;
		}
	};

} //namespace gargantua