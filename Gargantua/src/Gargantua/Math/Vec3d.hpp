#pragma once
/*
Gargantua/Math/Vec3d.hpp


PURPOSE: Vector 3d.


CLASSES:
	Vec3d: vector 3d with x, y and z components.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec2d.hpp"

#include <type_traits>
#include <cmath>
#include <string>
#include <format>

namespace Gargantua
{
	namespace Math
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


			T& operator[](std::size_t idx) { return reinterpret_cast<T*>(&x)[idx]; }
			T operator[](std::size_t idx) const { return reinterpret_cast<const T*>(&x)[idx]; }


			inline Vec3d& operator+=(const Vec3d& rhs)
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				return *this;
			}


			inline Vec3d& operator-=(const Vec3d& rhs)
			{
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;
				return *this;
			}


			inline Vec3d& operator*=(const T c)
			{
				x *= c;
				y *= c;
				z *= c;
				return *this;
			}


			inline Vec3d& operator/=(const T c)
			{
				x /= c;
				y /= c;
				z /= c;
				return *this;
			}



			inline void Zero()
			{
				x = T{ 0 };
				y = T{ 0 };
				z = T{ 0 };
			}



			inline void Normalize()
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

			inline Vec3d Normalized()
			{
				Vec3d copy = *this;
				copy.Normalize();
				return copy;
			}


			inline T Length() const
			{
				return std::sqrt(x * x + y * y + z * z);
			}


			inline T Dot(const Vec3d& rhs) const
			{
				return x * rhs.x + y * rhs.y + z * rhs.z;
			}


			std::string ToString()
			{
				return std::format("( {}  {}  {})", x, y, z);
			}


		public:
			T x{ 0 };
			T y{ 0 };
			T z{ 0 };
		};


		/**************** TYPE ALIAS ************************/
		using Vec3di = Vec3d<integer_t>;
		using Vec3df = Vec3d<real_t>;
		/**************** TYPE ALIAS ************************/



		/*****************************************************************/
		//                  INLINE OPERATORS 
		/*****************************************************************/

		template <typename T>
		inline bool operator==(const Vec3d<T>& lhs, const Vec3d<T>& rhs)
		{
			return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
		}

		template <typename T>
		inline bool operator!=(const Vec3d<T>& lhs, const Vec3d<T>& rhs)
		{
			return !(lhs == rhs);
		}


		template <typename T>
		inline Vec3d<T> operator+(Vec3d<T> lhs, const Vec3d<T>& rhs)
		{
			lhs += rhs;
			return lhs;
		}


		template <typename T>
		inline Vec3d<T> operator-(Vec3d<T> lhs, const Vec3d<T>& rhs)
		{
			lhs -= rhs;
			return lhs;
		}


		template <typename T, typename U>
			requires std::is_arithmetic_v<U>
		inline Vec3d<T> operator*(Vec3d<T> lhs, const U c)
		{
			lhs *= (T)c;
			return lhs;
		}


		template <typename T, typename U>
			requires std::is_arithmetic_v<U>
		inline Vec3d<T> operator/(Vec3d<T> lhs, const U c)
		{
			lhs /= (T)c;
			return lhs;
		}
	} //namespace Math
} //namespace Gargantua

