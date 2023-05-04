/*
gargantua/math/vec4d.ixx


PURPOSE: Homogeneous Vector 4d.


CLASSES:
	Vec4d: vector 4d with x, y, z and w components.

DESCRIPTION:
	This can represent an Homogeneous vector 4d. This means that the ordinary operations between vectors are
	defined only if w is equal to 0. Remember that we can't add 2 points (it has no meaning) but we can add 2 vectors or 1 point
	with 1 vector. A vector (in homogeneous coord) is defined with w = 0.
	For more: https://math.stackexchange.com/questions/376300/addition-of-homogeneous-vectors-with-different-w-component
	So if this class is intended to be used as homogeneous vec, keep in mind the constraints.

*/

export module gargantua.math.vec4d;

import <type_traits>;
import <cmath>;
import <string>;
import <format>;

import gargantua.math.vec2d;
import gargantua.math.vec3d;
import gargantua.types;


export namespace gargantua::math
{

	template <typename T>
		requires std::is_arithmetic_v<T>
	class Vec4d
	{
	public:
		using value_type = T;

		Vec4d() = default;

		Vec4d(const T x_, const T y_, const T z_, const T w_) : x(x_), y(y_), z(z_), w(w_)
		{

		}

		Vec4d(const Vec2d<T>& v, const T z_, const T w_) : x(v.x), y(v.y), z(z_), w(w_)
		{

		}

		Vec4d(const Vec3d<T>& v, const T w_) : x(v.x), y(v.y), z(v.z), w(w_)
		{

		}

		// TODO: this is so unsafe.
		auto operator[](u32 idx) -> T&
		{ 
			return reinterpret_cast<T*>(&x)[idx]; 
		}


		auto operator[](u32 idx) const -> T
		{ 
			return reinterpret_cast<const T*>(&x)[idx]; 
		}


		auto operator+=(const Vec4d& rhs) -> Vec4d&
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}


		auto operator-=(const Vec4d& rhs) -> Vec4d&
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}


		auto operator*=(const T c) -> Vec4d&
		{
			x *= c;
			y *= c;
			z *= c;
			w *= c;
			return *this;
		}


		auto operator/=(const T c) -> Vec4d&
		{
			x /= c;
			y /= c;
			z /= c;
			w /= c;
			return *this;
		}



		auto Zero() -> void
		{
			x = T{ 0 };
			y = T{ 0 };
			z = T{ 0 };
			w = T{ 0 };
		}


		auto Normalize() -> void
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

		auto Normalized() -> Vec4d
		{
			Vec4d copy = *this;
			copy.Normalize();
			return copy;
		}


		auto Length() const -> T
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		auto LengthSqr() const noexcept -> T
		{
			return x * x + y * y + z * z + w * w;
		}


		auto Dot(const Vec4d& rhs) const noexcept -> T
		{
			return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
		}


		auto ToString() const -> std::string
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
	using Vec4df = Vec4d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/

	template <typename T>
	inline auto operator==(const Vec4d<T>& lhs, const Vec4d<T>& rhs) -> bool
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.w == rhs.w);
	}

	template <typename T>
	inline auto operator!=(const Vec4d<T>& lhs, const Vec4d<T>& rhs) -> bool
	{
		return !(lhs == rhs);
	}


	template <typename T>
	inline auto operator+(Vec4d<T> lhs, const Vec4d<T>& rhs) -> Vec4d<T>
	{
		lhs += rhs;
		return lhs;
	}


	template <typename T>
	inline auto operator-(Vec4d<T> lhs, const Vec4d<T>& rhs) -> Vec4d<T>
	{
		lhs -= rhs;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator*(Vec4d<T> lhs, const U c) -> Vec4d<T>
	{
		lhs *= (T)c;
		return lhs;
	}

	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator*(const U c, Vec4d<T> lhs) -> Vec4d<T>
	{
		lhs *= (T)c;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator/(Vec4d<T> lhs, const U c) -> Vec4d<T>
	{
		lhs /= (T)c;
		return lhs;
	}

	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator/(const U c, Vec4d<T> lhs) -> Vec4d<T>
	{
		lhs /= (T)c;
		return lhs;
	}

} //namespace gargantua::math
