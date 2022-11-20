/*
gargantua/math/vec2d.ixx


PURPOSE: Vector 2d.


CLASSES:
	Vec2d: vector 2d with x and y components.
*/

export module gargantua.math.vec2d;

import <type_traits>;
import <cmath>;
import <string>;
import <format>;

import gargantua.types;


export namespace gargantua::math
{

	template <typename T>
		requires std::is_arithmetic_v<T>
	class Vec2d
	{
	public:
		using value_type = T;

		Vec2d() = default;

		Vec2d(const T x_, const T y_) : x(x_), y(y_)
		{

		}


		//TODO: CHANGE THIS CODE. DON'T USE REINTERPRET_CAST
		auto operator[](std::size_t idx) -> T& 
		{ 
			return reinterpret_cast<T*>(&x)[idx]; 
		}


		auto operator[](std::size_t idx) const -> T 
		{ 
			return reinterpret_cast<const T*>(&x)[idx]; 
		}


		auto operator+=(const Vec2d& rhs) -> Vec2d&
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}


		auto operator-=(const Vec2d& rhs) -> Vec2d&
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}


		auto operator*=(const T c) -> Vec2d&
		{
			x *= c;
			y *= c;
			return *this;
		}


		auto operator/=(const T c) -> Vec2d&
		{
			x /= c;
			y /= c;
			return *this;
		}



		auto Zero() -> void
		{
			x = T{ 0 };
			y = T{ 0 };
		}



		auto Normalize() -> void
		{
			T l = x * x + y * y;
			if (l != 0)
			{
				l = std::sqrt(l);
				x /= l;
				y /= l;
			}
		}


		auto Normalized() -> Vec2d
		{
			Vec2d copy = *this;
			copy.Normalize();
			return copy;
		}


		auto Length() const -> T
		{
			return std::sqrt(x * x + y * y);
		}


		auto LengthSqr() const -> T
		{
			return x * x + y * y;
		}


		auto Dot(const Vec2d& rhs) const -> T
		{
			return x * rhs.x + y * rhs.y;
		}


		auto ToString() -> std::string
		{
			return std::format("( {}  {} )", x, y);
		}


	public:
		T x{ 0 };
		T y{ 0 };
	}; //class Vec2d

	/**************** TYPE ALIAS ************************/
	using Vec2di = Vec2d<integer_t>;
	using Vec2df = Vec2d<real_t>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/

	template <typename T>
	inline auto operator==(const Vec2d<T>& lhs, const Vec2d<T>& rhs) -> bool
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	template <typename T>
	inline auto operator!=(const Vec2d<T>& lhs, const Vec2d<T>& rhs) -> bool
	{
		return !(lhs == rhs);
	}


	template <typename T>
	inline auto operator+(Vec2d<T> lhs, const Vec2d<T>& rhs) -> Vec2d<T>
	{
		lhs += rhs;
		return lhs;
	}


	template <typename T>
	inline auto operator-(Vec2d<T> lhs, const Vec2d<T>& rhs) -> Vec2d<T>
	{
		lhs -= rhs;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator*(Vec2d<T> lhs, const U c) -> Vec2d<T>
	{
		lhs *= (T)c;
		return lhs;
	}

	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator*(const U c, Vec2d<T> lhs) -> Vec2d<T>
	{
		lhs *= (T)c;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator/(Vec2d<T> lhs, const U c) -> Vec2d<T>
	{
		lhs /= (T)c;
		return lhs;
	}

	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator/(const U c, Vec2d<T> lhs) -> Vec2d<T>
	{
		lhs /= (T)c;
		return lhs;
	}


	template <typename T>
	inline auto operator-(const Vec2d<T>& v) -> Vec2d<T>
	{
		return Vec2d<T>{-v.x, -v.y};
	}

} //namespace gargantua::math

