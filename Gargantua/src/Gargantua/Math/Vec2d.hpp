#pragma once

#include "Gargantua/Types.hpp"

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
		class Vec2d
		{
		public:
			using value_type = T;

			Vec2d() = default;

			Vec2d(const T x_, const T y_) : x(x_), y(y_)
			{

			}


			T& operator[](std::size_t idx) { return reinterpret_cast<T*>(&x)[idx]; }
			T operator[](std::size_t idx) const { return reinterpret_cast<const T*>(&x)[idx]; }

			
			inline Vec2d& operator+=(const Vec2d& rhs)
			{
				x += rhs.x;
				y += rhs.y;
				return *this;
			}


			inline Vec2d& operator-=(const Vec2d& rhs)
			{
				x -= rhs.x;
				y -= rhs.y;
				return *this;
			}


			inline Vec2d& operator*=(const T c)
			{
				x *= c;
				y *= c;
				return *this;
			}


			inline Vec2d& operator/=(const T c)
			{
				x /= c;
				y /= c;
				return *this;
			}
			


			inline void Zero()
			{
				x = T{ 0 };
				y = T{ 0 };
			}


			
			inline void Normalize()
			{
				T l = x * x + y * y;
				if (l != 0)
				{
					l = std::sqrt(l);
					x /= l;
					y /= l;
				}
			}

			inline Vec2d Normalized()
			{
				Vec2d copy = *this;
				copy.Normalize();
				return copy;
			}


			inline T Length() const
			{
				return std::sqrt(x * x + y * y);
			}


			inline T Dot(const Vec2d& rhs) const
			{
				return x * rhs.x + y * rhs.y;
			}


			std::string ToString()
			{
				return std::format("( x : {}, y : {} )", x, y);
			}


		public:
			T x{0};
			T y{0};
		};


		using Vec2di = Vec2d<integer_t>;
		using Vec2df = Vec2d<real_t>;


		template <typename T> 
		inline bool operator==(const Vec2d<T>& lhs, const Vec2d<T>& rhs)
		{
			return (lhs.x == rhs.x) && (lhs.y == rhs.y);
		}

		template <typename T>
		inline bool operator!=(const Vec2d<T>& lhs, const Vec2d<T>& rhs)
		{
			return !(lhs == rhs);
		}


		template <typename T>
		inline Vec2d<T> operator+(Vec2d<T> lhs, const Vec2d<T>& rhs)
		{
			lhs += rhs;
			return lhs;
		}


		template <typename T>
		inline Vec2d<T> operator-(Vec2d<T> lhs, const Vec2d<T>& rhs)
		{
			lhs -= rhs;
			return lhs;
		}


		template <typename T, typename U>
		requires std::is_arithmetic_v<U>
		inline Vec2d<T> operator*(Vec2d<T> lhs, const U c)
		{
			lhs *= (T)c;
			return lhs;
		}


		template <typename T, typename U>
		requires std::is_arithmetic_v<U>
		inline Vec2d<T> operator/(Vec2d<T> lhs, const U c)
		{
			lhs /= (T)c;
			return lhs;
		}


	} //namespace Math
} //namespace Gargantua

