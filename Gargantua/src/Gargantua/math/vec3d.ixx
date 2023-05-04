/*
gargantua/math/vec3d.ixx


PURPOSE: Vector 3d.


CLASSES:
	Vec3d: vector 3d with x, y and z components.
*/

export module gargantua.math.vec3d;

import <type_traits>;
import <cmath>;
import <string>;
import <format>;

import gargantua.math.vec2d;
import gargantua.types;


export namespace gargantua::math
{

	template <typename T>
		requires std::is_arithmetic_v<T>
	class Vec3d
	{
	public:
		using value_type = T;

		Vec3d() = default;

		Vec3d(const T x_, const T y_, const T z_) : x(x_), y(y_), z(z_)
		{

		}

		Vec3d(const Vec2d<T>& v, const T z_) : x(v.x), y(v.y), z(z_)
		{

		}


		//TODO: CHANGE THIS CODE. DON'T USE REINTERPRET_CAST
		auto operator[](u32 idx) -> T& 
		{ 
			return reinterpret_cast<T*>(&x)[idx]; 
		}


		auto operator[](u32 idx) const -> T
		{ 
			return reinterpret_cast<const T*>(&x)[idx]; 
		}


		auto operator+=(const Vec3d& rhs) -> Vec3d&
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}


		auto operator-=(const Vec3d& rhs) -> Vec3d&
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}


		auto operator*=(const T c) -> Vec3d&
		{
			x *= c;
			y *= c;
			z *= c;
			return *this;
		}


		auto operator/=(const T c) -> Vec3d&
		{
			x /= c;
			y /= c;
			z /= c;
			return *this;
		}



		auto Zero() noexcept -> void
		{
			x = T{ 0 };
			y = T{ 0 };
			z = T{ 0 };
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


		auto Normalized() -> Vec3d
		{
			Vec3d copy = *this;
			copy.Normalize();
			return copy;
		}


		auto Length() const -> T
		{
			return std::sqrt(x * x + y * y + z * z);
		}


		auto LengthSqr() const noexcept -> T 
		{
			return x * x + y * y + z * z;
		}


		auto Dot(const Vec3d& rhs) const noexcept -> T
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}


		auto ToString() const -> std::string
		{
			return std::format("( {}  {}  {})", x, y, z);
		}


	public:
		T x{ 0 };
		T y{ 0 };
		T z{ 0 };
	}; //class Vec3d


	/**************** TYPE ALIAS ************************/
	using Vec3di = Vec3d<i32>;
	using Vec3df = Vec3d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/

	template <typename T>
	inline auto operator==(const Vec3d<T>& lhs, const Vec3d<T>& rhs) -> bool
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
	}

	template <typename T>
	inline auto operator!=(const Vec3d<T>& lhs, const Vec3d<T>& rhs) -> bool
	{
		return !(lhs == rhs);
	}


	template <typename T>
	inline auto operator+(Vec3d<T> lhs, const Vec3d<T>& rhs) -> Vec3d<T>
	{
		lhs += rhs;
		return lhs;
	}


	template <typename T>
	inline auto operator-(Vec3d<T> lhs, const Vec3d<T>& rhs) -> Vec3d<T>
	{
		lhs -= rhs;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator*(Vec3d<T> lhs, const U c) -> Vec3d<T>
	{
		lhs *= (T)c;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator/(Vec3d<T> lhs, const U c) -> Vec3d<T>
	{
		lhs /= (T)c;
		return lhs;
	}

} //namespace gargantua::math

