/*
* gargantua/math/math_vec3d.ixx
* 
* PURPOSE: Vector 3d.
* 
* CLASSES:
* 	Vec3d: vector 3d with x, y and z components.
*/

module;

#include <gargantua/log/logger_macro.hpp>

export module gargantua.math.vec3d;


import <concepts>;
import <cmath>;
import <string>;
import <format>;
import <compare>;
import <stdexcept>;

import gargantua.types;
import gargantua.math.concepts;
import gargantua.math.vec2d;
import gargantua.log;


export namespace gargantua::math
{

	template <CIsArithmetic T>
	class Vec3d
	{
	public:
		using value_type = T;

		constexpr explicit Vec3d() noexcept = default;

		constexpr explicit Vec3d(const T x_, const T y_, const T z_) noexcept : x(x_), y(y_), z(z_)
		{

		}

		constexpr explicit Vec3d(const Vec2d<T>& v, const T z_) noexcept : x(v.x), y(v.y), z(z_)
		{

		}


		constexpr auto operator==(const Vec3d&) const noexcept -> bool = default;


		template <std::convertible_to<T> U>
		constexpr explicit operator Vec3d<U>() const noexcept
		{
			return Vec3d<U>{static_cast<U>(x), static_cast<U>(y), static_cast<U>(z)};
		}


		// https://developercommunity.visualstudio.com/t/ICE-when-using-explicit-this-parameterD/10236618
		// almost 1 year for this bug. :D 
		/*constexpr auto&& operator[](this auto&& self, const u32 idx)
		{
			switch (idx)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
			}
			GRG_CORE_ERROR("Vec3d access with idx {}", idx);
			throw std::out_of_range{ "Vec3d access error" };
		}*/
		[[nodiscard]]
		constexpr auto operator[](const u32 idx) const -> T
		{
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			}
			GRG_CORE_ERROR("Vec3d access with idx {}", idx);
			throw std::out_of_range{ "Vec3d access error" };
		}

		[[nodiscard]]
		constexpr auto operator[](const u32 idx) -> T&
		{
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			}
			GRG_CORE_ERROR("Vec3d access with idx {}", idx);
			throw std::out_of_range{ "Vec3d access error" };
		}


		constexpr auto operator+=(const Vec3d& rhs) noexcept -> Vec3d&
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}


		constexpr auto operator-=(const Vec3d& rhs) noexcept -> Vec3d&
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}


		constexpr auto operator*=(const T c) noexcept -> Vec3d&
		{
			x *= c;
			y *= c;
			z *= c;
			return *this;
		}


		constexpr auto operator/=(const T c) -> Vec3d&
		{
			x /= c;
			y /= c;
			z /= c;
			return *this;
		}



		constexpr auto Zero() noexcept -> void
		{
			x = T{ 0 };
			y = T{ 0 };
			z = T{ 0 };
		}



		constexpr auto Normalize() -> void
		{
			T l = x * x + y * y + z * z;
			if (l != 0)
			{
				l = std::sqrt(l);
				x /= l;
				y /= l;
				z /= l;
			}
		}

		[[nodiscard]]
		constexpr auto Normalized() const -> Vec3d
		{
			Vec3d copy = *this;
			copy.Normalize();
			return copy;
		}

		[[nodiscard]]
		constexpr auto Length() const noexcept -> T
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		[[nodiscard]]
		constexpr auto LengthSqr() const noexcept -> T
		{
			return x * x + y * y + z * z;
		}

		[[nodiscard]]
		constexpr auto Dot(const Vec3d& rhs) const noexcept -> T
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}

		[[nodiscard]]
		constexpr auto ToString() const -> std::string
		{
			return std::format("( {}  {}  {})", x, y, z);
		}


	public:
		T x{ 0 };
		T y{ 0 };
		T z{ 0 };
	}; 


	/**************** TYPE ALIAS ************************/
	using Vec3di = Vec3d<i32>;
	using Vec3du = Vec3d<u32>;
	using Vec3df = Vec3d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                   OPERATORS 
	/*****************************************************************/


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator+(const Vec3d<T>& lhs, const Vec3d<T>& rhs) noexcept -> Vec3d<T>
	{
		return Vec3d<T>{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator-(const Vec3d<T>& lhs, const Vec3d<T>& rhs) noexcept -> Vec3d<T>
	{
		return Vec3d<T>{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator*(const Vec3d<T>& lhs, const T c) noexcept -> Vec3d<T>
	{
		return Vec3d<T>{ lhs.x * c, lhs.y * c, lhs.z * c };
	}

	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator*(const T c, const Vec3d<T>& lhs) noexcept -> Vec3d<T>
	{
		return Vec3d<T>{ lhs.x * c, lhs.y * c, lhs.z * c };
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator/(Vec3d<T> lhs, const T c) -> Vec3d<T>
	{
		return Vec3d<T>{ lhs.x / c, lhs.y / c, lhs.z / c };
	}

} //namespace gargantua::math

