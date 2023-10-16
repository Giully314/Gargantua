/*
* gargantua/math/vec2d.ixx
* 
* PURPOSE: Vector 2d.
* 
* CLASSES:
* 	Vec2d: vector 2d with x and y components.
*/

module;

#include <gargantua/log/logger_macro.hpp>

export module gargantua.math.vec2d;

import <type_traits>;
import <concepts>;
import <cmath>;
import <string>;
import <format>;
import <compare>;
import <stdexcept>;

import gargantua.types;
import gargantua.log;


export namespace gargantua::math
{

	template <typename T>
		requires std::is_arithmetic_v<T>
	class Vec2d
	{
	public:
		using value_type = T;

		constexpr Vec2d() noexcept = default;


		constexpr Vec2d(const T x_, const T y_) noexcept : x(x_), y(y_)
		{

		}


		constexpr auto operator==(const Vec2d&) const -> bool = default;
	
		
		template <std::convertible_to<T> U> 
		constexpr operator Vec2d<U>() const noexcept 
		{
			return Vec2d<U>{static_cast<U>(x), static_cast<U>(y)};
		}

		// https://developercommunity.visualstudio.com/t/ICE-when-using-explicit-this-parameterD/10236618
		// almost 1 year for this bug. :D 
		/*constexpr auto&& operator[](this auto&& self, const u32 idx) 
		{
			switch (idx)
			{
				case 0: return x;
				case 1: return y;
			}
			GRG_CORE_ERROR("Vec2d access with idx {}", idx);
			throw std::out_of_range{ "Vec2d access error" };
		}*/

		[[nodiscard]]
		constexpr auto operator[](const u32 idx) const -> T
		{
			switch (idx)
			{
				case 0: return x;
				case 1: return y;
			}
			GRG_CORE_ERROR("Vec2d access with idx {}", idx);
			throw std::out_of_range{ "Vec2d access error" };
		}


		[[nodiscard]]
		constexpr auto operator[](const u32 idx) -> T&
		{
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			}
			GRG_CORE_ERROR("Vec2d access with idx {}", idx);
			throw std::out_of_range{ "Vec2d access error" };
		}


		constexpr auto operator+=(const Vec2d& rhs) noexcept -> Vec2d&
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}


		constexpr auto operator-=(const Vec2d& rhs) noexcept -> Vec2d&
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}


		constexpr auto operator*=(const T c) noexcept -> Vec2d&
		{
			x *= c;
			y *= c;
			return *this;
		}

		
		constexpr auto operator/=(const T c) noexcept -> Vec2d&
		{
			x /= c;
			y /= c;
			return *this;
		}


		auto Zero() noexcept -> void
		{
			x = T{ 0 };
			y = T{ 0 };
		}


		constexpr auto Normalize() -> void
		{
			T l = x * x + y * y;
			if (l != 0)
			{
				l = std::sqrt(l);
				x /= l;
				y /= l;
			}
		}


		[[nodiscard]]
		constexpr auto Normalized() const -> Vec2d
		{
			Vec2d copy = *this;
			copy.Normalize();
			return copy;
		}


		[[nodiscard]]
		constexpr auto Length() const noexcept -> T
		{
			return std::sqrt(x * x + y * y);
		}


		[[nodiscard]]
		constexpr auto LengthSqr() const noexcept -> T
		{
			return x * x + y * y;
		}


		[[nodiscard]]
		constexpr auto Dot(const Vec2d& rhs) const noexcept -> T
		{
			return x * rhs.x + y * rhs.y;
		}


		[[nodiscard]]
		constexpr auto ToString() const -> std::string
		{
			return std::format("( {}  {} )", x, y);
		}

	public:
		T x{ 0 };
		T y{ 0 };
	}; 

	/**************** TYPE ALIAS ************************/
	using Vec2di = Vec2d<i32>;
	using Vec2df = Vec2d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  OPERATORS 
	/*****************************************************************/


	template <typename T>
	[[nodiscard]]
	constexpr auto operator+(const Vec2d<T>& lhs, const Vec2d<T>& rhs) noexcept -> Vec2d<T>
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}


	template <typename T>
	[[nodiscard]]
	constexpr auto operator-(const Vec2d<T>& lhs, const Vec2d<T>& rhs) noexcept -> Vec2d<T>
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator*(const Vec2d<T>& lhs, const U c) noexcept -> Vec2d<decltype(c * lhs.x)>
	{
		return { c * lhs.x, c * lhs.y };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator*(const U c, const Vec2d<T>& lhs) noexcept -> Vec2d<decltype(c * lhs.x)>
	{
		return { c * lhs.x, c * lhs.y };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator/(const Vec2d<T>& lhs, const U c) -> Vec2d<decltype(c / lhs.x)>
	{
		return { lhs.x / c, lhs.y / c };
	}


	template <typename T>
	[[nodiscard]]
	constexpr auto operator-(const Vec2d<T>& v) noexcept -> Vec2d<T>
	{
		return Vec2d<T>{-v.x, -v.y};
	}

} //namespace gargantua::math

