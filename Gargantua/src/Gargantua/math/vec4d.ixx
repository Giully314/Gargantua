/*
* gargantua/math/vec4d.ixx
* 
* 
* PURPOSE: Vector 4d.
* 
* 
* CLASSES:
* 	Vec4d: vector 4d with x, y, z and w components.
* 
* DESCRIPTION:
* 	This can represent an Homogeneous vector 4d. This means that the ordinary operations between vectors are
* 	defined only if w is equal to 0. Remember that we can't add 2 points (it has no meaning) but we can add 2 vectors or 1 point
* 	with 1 vector. A vector (in homogeneous coord) is defined with w = 0.
* 	For more: https://math.stackexchange.com/questions/376300/addition-of-homogeneous-vectors-with-different-w-component
* 	So if this class is intended to be used as homogeneous vec, keep in mind the constraints.
* 
*/

module;

#include <gargantua/log/logger_macro.hpp>

export module gargantua.math.vec4d;

import <type_traits>;
import <concepts>;
import <cmath>;
import <string>;
import <format>;
import <compare>;

import gargantua.types;
import gargantua.math.vec2d;
import gargantua.math.vec3d;
import gargantua.log;

export namespace gargantua::math
{

	template <typename T>
		requires std::is_arithmetic_v<T>
	class Vec4d
	{
	public:
		using value_type = T;

		constexpr Vec4d() noexcept = default;

		constexpr Vec4d(const T x_, const T y_, const T z_, const T w_) noexcept : x(x_), y(y_), z(z_), w(w_)
		{

		}


		constexpr Vec4d(const Vec2d<T>& v, const T z_, const T w_) noexcept : x(v.x), y(v.y), z(z_), w(w_)
		{

		}


		constexpr Vec4d(const Vec3d<T>& v, const T w_) noexcept : x(v.x), y(v.y), z(v.z), w(w_)
		{

		}


		constexpr auto operator==(const Vec4d&) const -> bool = default;


		template <std::convertible_to<T> U>
		constexpr operator Vec4d<U>() const noexcept
		{
			return Vec4d<U>{static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(w)};
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
				case 3: return w;
			}
			GRG_CORE_ERROR("Vec4d access with idx {}", idx);
			throw std::out_of_range{ "Vec4d access error" };
		}*/
		[[nodiscard]]
		constexpr auto operator[](const u32 idx) const -> T
		{
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			}
			GRG_CORE_ERROR("Vec4d access with idx {}", idx);
			throw std::out_of_range{ "Vec4d access error" };
		}


		[[nodiscard]]
		constexpr auto operator[](const u32 idx) -> T&
		{
			switch (idx)
			{
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			}
			GRG_CORE_ERROR("Vec4d access with idx {}", idx);
			throw std::out_of_range{ "Vec4d access error" };
		}


		constexpr auto operator+=(const Vec4d& rhs) noexcept -> Vec4d&
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}


		constexpr auto operator-=(const Vec4d& rhs) noexcept -> Vec4d&
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}


		constexpr auto operator*=(const T c) noexcept -> Vec4d&
		{
			x *= c;
			y *= c;
			z *= c;
			w *= c;
			return *this;
		}


		constexpr auto operator/=(const T c) -> Vec4d&
		{
			x /= c;
			y /= c;
			z /= c;
			w /= c;
			return *this;
		}


		constexpr auto Zero() noexcept -> void
		{
			x = T{ 0 };
			y = T{ 0 };
			z = T{ 0 };
			w = T{ 0 };
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
		constexpr auto Normalized() const -> Vec4d
		{
			Vec4d copy = *this;
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
			return x * x + y * y + z * z + w * w;
		}


		[[nodiscard]]
		constexpr auto Dot(const Vec4d& rhs) const noexcept -> T
		{
			return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
		}


		[[nodiscard]]
		constexpr auto ToString() const -> std::string
		{
			return std::format("( {}  {}  {}  {} )", x, y, z, w);
		}


	public:
		T x{ 0 };
		T y{ 0 };
		T z{ 0 };
		T w{ 0 };
	};


	/**************** TYPE ALIAS ************************/
	using Vec4di = Vec4d<i32>;
	using Vec4du = Vec4d<u32>;
	using Vec4df = Vec4d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/


	template <typename T>
	[[nodiscard]]
	constexpr auto operator+(const Vec4d<T>& lhs, const Vec4d<T>& rhs) noexcept -> Vec4d<T>
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
	}


	template <typename T>
	[[nodiscard]]
	constexpr auto operator-(Vec4d<T> lhs, const Vec4d<T>& rhs) noexcept -> Vec4d<T>
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator*(const Vec4d<T>& lhs, const U c) noexcept -> Vec4d<decltype(c * lhs.x)>
	{
		return { c * lhs.x, c * lhs.y, c * lhs.z, c * lhs.w };
	}



	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator*(const U c, const Vec4d<T>& lhs) noexcept -> Vec4d<decltype(c* lhs.x)>
	{
		return { c * lhs.x, c * lhs.y, c * lhs.z, c * lhs.w };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator/(Vec4d<T> lhs, const U c) -> Vec4d<decltype(c* lhs.x)>
	{
		return { lhs.x / c, lhs.y / c, lhs.z / c, lhs.w / c };
	}

} //namespace gargantua::math
