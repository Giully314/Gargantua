#pragma once
/*
Gargantua/Math/Vec4d.hpp


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

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec2d.hpp"
#include "Gargantua/Math/Vec3d.hpp"

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


			T& operator[](std::size_t idx) { return reinterpret_cast<T*>(&x)[idx]; }
			T operator[](std::size_t idx) const { return reinterpret_cast<const T*>(&x)[idx]; }


			Vec4d& operator+=(const Vec4d& rhs)
			{
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				w += rhs.w;
				return *this;
			}


			Vec4d& operator-=(const Vec4d& rhs)
			{
				x -= rhs.x;
				y -= rhs.y;
				z -= rhs.z;
				w -= rhs.w;
				return *this;
			}


			Vec4d& operator*=(const T c)
			{
				x *= c;
				y *= c;
				z *= c;
				w *= c;
				return *this;
			}


			Vec4d& operator/=(const T c)
			{
				x /= c;
				y /= c;
				z /= c;
				w /= c;
				return *this;
			}



			void Zero()
			{
				x = T{ 0 };
				y = T{ 0 };
				z = T{ 0 };
				w = T{ 0 };
			}


			void Normalize()
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

			Vec4d Normalized()
			{
				Vec4d copy = *this;
				copy.Normalize();
				return copy;
			}


			T Length() const
			{
				return std::sqrt(x * x + y * y + z * z);
			}

			T LengthSqr() const
			{
				return x * x + y * y + z * z + w * w;
			}


			T Dot(const Vec4d& rhs) const
			{
				return x * rhs.x + y * rhs.y + z * rhs.z;
			}


			std::string ToString()
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
		using Vec4di = Vec4d<integer_t>;
		using Vec4df = Vec4d<real_t>;
		/**************** TYPE ALIAS ************************/



		/*****************************************************************/
		//                  INLINE OPERATORS 
		/*****************************************************************/

		template <typename T>
		inline bool operator==(const Vec4d<T>& lhs, const Vec4d<T>& rhs)
		{
			return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.w == rhs.w);
		}

		template <typename T>
		inline bool operator!=(const Vec4d<T>& lhs, const Vec4d<T>& rhs)
		{
			return !(lhs == rhs);
		}


		template <typename T>
		inline Vec4d<T> operator+(Vec4d<T> lhs, const Vec4d<T>& rhs)
		{
			lhs += rhs;
			return lhs;
		}


		template <typename T>
		inline Vec4d<T> operator-(Vec4d<T> lhs, const Vec4d<T>& rhs)
		{
			lhs -= rhs;
			return lhs;
		}


		template <typename T, typename U>
			requires std::is_arithmetic_v<U>
		inline Vec4d<T> operator*(Vec4d<T> lhs, const U c)
		{
			lhs *= (T)c;
			return lhs;
		}

		template <typename T, typename U>
			requires std::is_arithmetic_v<U>
		inline Vec4d<T> operator*(const U c, Vec4d<T> lhs)
		{
			lhs *= (T)c;
			return lhs;
		}


		template <typename T, typename U>
			requires std::is_arithmetic_v<U>
		inline Vec4d<T> operator/(Vec4d<T> lhs, const U c)
		{
			lhs /= (T)c;
			return lhs;
		}

		template <typename T, typename U>
			requires std::is_arithmetic_v<U>
		inline Vec4d<T> operator/(const U c, Vec4d<T> lhs)
		{
			lhs /= (T)c;
			return lhs;
		}
	} //namespace Math
} //namespace Gargantua
