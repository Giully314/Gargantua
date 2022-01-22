#pragma once

#include "Gargantua/Math/Vec2d.hpp"

#include <type_traits>
#include <string>
#include <format>

namespace Gargantua
{
	namespace Math
	{
		template <typename T> 
		requires std::is_arithmetic_v<T>
		class Mat2d
		{
		public:
			using value_type = T;

			Mat2d() = default;

			Mat2d(const Vec2d<T> row1, const Vec2d<T> row2)
			{
				m[0] = std::move(row1);
				m[1] = std::move(row2);
			}

			Mat2d(const T a, const T b, const T c, const T d) : m{ Vec2d<T>{a, b}, Vec2d<T>{c, d} }
			{
				
			}
			

			T& operator()(const std::size_t i, const std::size_t j)
			{
				return m[i][j];
			}

			T operator()(const std::size_t i, const std::size_t j) const
			{
				return m[i][j];
			}


			//return row i
			Vec2d<T>& operator()(const std::size_t i)
			{
				return m[i];
			}

			const Vec2d<T>& operator()(const std::size_t i) const
			{
				return m[i];
			}



			inline Mat2d& operator+=(const Mat2d& rhs)
			{
				m[0] += rhs.m[0];
				m[1] += rhs.m[1];
				return *this;
			}

			inline friend Mat2d operator+(Mat2d lhs, const Mat2d& rhs)
			{
				lhs += rhs;
				return lhs;
			}


			inline Mat2d& operator-=(const Mat2d& rhs)
			{
				m[0] -= rhs.m[0];
				m[1] -= rhs.m[1];
				return *this;
			}

			inline friend Mat2d operator-(Mat2d lhs, const Mat2d& rhs)
			{
				lhs -= rhs;
				return lhs;
			}


			inline Mat2d& operator*=(const T c)
			{
				m[0] *= c;
				m[1] *= c;
				return *this;
			}

			inline friend Mat2d operator*(Mat2d lhs, const T c)
			{
				lhs *= c;
				return lhs;
			}

			inline Mat2d& operator*=(const Mat2d& rhs)
			{
				T x = m[0][0];
				T y = m[0][1];
		
				m[0][0] = x * rhs.m[0][0] + y * rhs.m[1][0];
				m[0][1] = x * rhs.m[1][0] + y * rhs.m[1][1];
				
				x = m[1][0];
				y = m[1][1];
				m[1][0] = x * rhs.m[0][0] + y * rhs.m[1][0];
				m[1][1] = x * rhs.m[1][0] + y * rhs.m[1][1];
				return *this;
			}

			inline friend Mat2d operator*(Mat2d lhs, const Mat2d& rhs)
			{
				lhs *= rhs;
				return lhs;
			}

			inline friend Vec2d<T> operator*(const Mat2d& lhs, const Vec2d<T>& rhs)
			{
				T x = lhs.m[0].Dot(rhs);
				T y = lhs.m[1].Dot(rhs);
				return Vec2d<T>{x, y};
			}



			inline Mat2d& operator/=(const T c)
			{
				m[0] /= c;
				m[1] /= c;
				return *this;
			}

			inline friend Mat2d operator/(Mat2d lhs, const T c)
			{
				lhs /= c;
				return lhs;
			}


			inline void Zero()
			{
				m[0].Zero();
				m[1].Zero();
			}

			inline void Identity()
			{
				m[0].x = T{ 1 };
				m[0].y = T{ 0 };

				m[1].x = T{ 0 };
				m[1].y = T{ 1 };
			}



			T Determinant() const
			{
				return m[0].x * m[1].y - m[0].y * m[1].x;
			}


			Mat2d Inverse() const
			{
				T d = Determinant();
				return Mat2d{ m[1][1] / d, -m[0][1] / d,
							-m[1][0] / d,  m[0][0] / d};
			}


			std::string ToString()
			{
				return std::format("( ({} {}), ({} {}) )", m[0][0], m[0][1], m[1][0], m[1][1]);
			}

		private:
			Vec2d<T> m[2];
		};


		using Mat2df = Mat2d<real_t>;
		using mat2di = Mat2d<integer_t>;

	} //namespace Math
} //namespace Gargantua