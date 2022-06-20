#pragma once
/*
Gargantua/Math/Mat2d.hpp


PURPOSE: Matrix 2x2.


CLASSES:
	Mat2d: matrix 2x2 with row representation.

DESCRIPTION:
	The internal format used is row-major order. Consider that this is only relevant in terms of 
	HOW operations are executed and not what they mean. 
*/

#include "Gargantua/Types.hpp"

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
			using col_t = Vec2d<T>; //column type
			using row_t = Vec2d<T>; //row type

			Mat2d() = default;

			//Initialize the diagonal of the matrix with the value d
			Mat2d(const T& d)
			{
				m[0][0] = d;
				m[1][1] = d;
			}

			Mat2d(row_t row0, row_t row1)
			{
				m[0] = std::move(row0);
				m[1] = std::move(row1);
			}

			Mat2d(const value_type a, const value_type b, const value_type c, const value_type d) : 
				m{ row_t{a, b}, row_t{c, d} }
			{
				
			}
			

			value_type& operator()(const natural_t i, const natural_t j)
			{
				return m[i][j];
			}

			value_type operator()(const natural_t i, const natural_t j) const
			{
				return m[i][j];
			}


			//return row i
			row_t& operator()(const natural_t i)
			{
				return m[i];
			}

			const row_t& operator()(const natural_t i) const
			{
				return m[i];
			}



			Mat2d& operator+=(const Mat2d& rhs)
			{
				m[0] += rhs.m[0];
				m[1] += rhs.m[1];
				return *this;
			}


			Mat2d& operator-=(const Mat2d& rhs)
			{
				m[0] -= rhs.m[0];
				m[1] -= rhs.m[1];
				return *this;
			}


			Mat2d& operator*=(const value_type c)
			{
				m[0] *= c;
				m[1] *= c;
				return *this;
			}


			Mat2d& operator*=(const Mat2d& rhs)
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


			Mat2d& operator/=(const value_type c)
			{
				m[0] /= c;
				m[1] /= c;
				return *this;
			}

		


			void Zero()
			{
				m[0].Zero();
				m[1].Zero();
			}

			void Identity()
			{
				m[0].x = value_type{ 1 };
				m[0].y = value_type{ 0 };

				m[1].x = value_type{ 0 };
				m[1].y = value_type{ 1 };
			}



			value_type Determinant() const
			{
				return m[0].x * m[1].y - m[0].y * m[1].x;
			}


			Mat2d Inverse() const
			{
				value_type d = Determinant();
				return Mat2d{ m[1][1] / d, -m[0][1] / d,
							-m[1][0] / d,  m[0][0] / d};
			}


			const value_type* GetAddress() const
			{
				return &(m[0].x);
			}

			value_type* GetAddress()
			{
				return &(m[0].x);
			}


			std::string ToString()
			{
				return std::format("{}\n{}", m[0].ToString(), m[1].ToString());
			}

		private:
			row_t m[2];
		};


		/**************** TYPE ALIAS ************************/
		using Mat2df = Mat2d<real_t>;
		using mat2di = Mat2d<integer_t>;
		/**************** TYPE ALIAS ************************/



		/*****************************************************************/
		//                  INLINE OPERATORS 
		/*****************************************************************/
		template <typename T>
		inline bool operator==(const Mat2d<T>& lhs, const Mat2d<T>& rhs)
		{
			return lhs(0) == rhs(0) && lhs(1) == rhs(1);
		}


		template <typename T>
		inline bool operator!=(const Mat2d<T>& lhs, const Mat2d<T>& rhs)
		{
			return !(lhs == rhs);
		}


		template <typename T>
		inline Mat2d<T> operator+(Mat2d<T> lhs, const Mat2d<T>& rhs)
		{
			lhs += rhs;
			return lhs;
		}


		template <typename T>
		inline Mat2d<T> operator-(Mat2d<T> lhs, const Mat2d<T>& rhs)
		{
			lhs -= rhs;
			return lhs;
		}

		
		template <typename T>
		inline Mat2d<T> operator*(Mat2d<T> lhs, const T c)
		{
			lhs *= c;
			return lhs;
		}


		template <typename T>
		inline Mat2d<T> operator/(Mat2d<T> lhs, const T c)
		{
			lhs /= c;
			return lhs;
		}


		template <typename T>
		inline Mat2d<T> operator*(Mat2d<T> lhs, const Mat2d<T>& rhs)
		{
			lhs *= rhs;
			return lhs;
		}


		template <typename T, typename U>
		inline Vec2d<std::common_type_t<T, U>> operator*(const Mat2d<T>& lhs, const Vec2d<U>& rhs)
		{
			using com_t = std::common_type_t<T, U>;
			com_t x = lhs(0).Dot(rhs);
			com_t y = lhs(1).Dot(rhs);
			return Vec2d<com_t>{x, y};
		}
	} //namespace Math
} //namespace Gargantua