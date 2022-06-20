#pragma once
/*
Gargantua/Math/Mat4d.hpp


PURPOSE: Matrix 4x4.


CLASSES:
	Mat4d: matrix 4x4 with row representation.

DESCRIPTION:
	The internal format used is row-major order. Consider that this is only relevant in terms of
	HOW operations are executed and not what they mean.

	The Inverse and the Determinant are calculated by writing the explicit formula based on cofactors.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec4d.hpp"

#include <type_traits>
#include <string>
#include <format>

namespace Gargantua
{
	namespace Math
	{
		template <typename T>
			requires std::is_arithmetic_v<T>
		class Mat4d
		{
		public:
			using value_type = T;
			using col_t = Vec4d<T>; //column type
			using row_t = Vec4d<T>; //row type
			inline static constexpr natural_t dim = 4;

			Mat4d() = default;

			//Initialize the diagonal of the matrix with the value d
			Mat4d(const T& d)
			{
				m[0][0] = d;
				m[1][1] = d;
				m[2][2] = d;
				m[3][3] = d;
			}

			Mat4d(row_t row0, row_t row1, row_t row2, row_t row3)
			{
				m[0] = std::move(row0);
				m[1] = std::move(row1);
				m[2] = std::move(row2);
				m[3] = std::move(row3);
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



			Mat4d& operator+=(const Mat4d& rhs)
			{
				m[0] += rhs.m[0];
				m[1] += rhs.m[1];
				m[2] += rhs.m[2];
				m[3] += rhs.m[3];
				return *this;
			}


			Mat4d& operator-=(const Mat4d& rhs)
			{
				m[0] -= rhs.m[0];
				m[1] -= rhs.m[1];
				m[2] -= rhs.m[2];
				m[3] -= rhs.m[3];
				return *this;
			}


			Mat4d& operator*=(const value_type c)
			{
				m[0] *= c;
				m[1] *= c;
				m[2] *= c;
				m[3] *= c;
				return *this;
			}


			Mat4d& operator*=(const Mat4d& rhs)
			{
				m[0] = m[0][0] * rhs.m[0] + m[0][1] * rhs.m[1] + m[0][2] * rhs.m[2] + m[0][3] * rhs.m[3];
				m[1] = m[1][0] * rhs.m[0] + m[1][1] * rhs.m[1] + m[1][2] * rhs.m[2] + m[1][3] * rhs.m[3];
				m[2] = m[2][0] * rhs.m[0] + m[2][1] * rhs.m[1] + m[2][2] * rhs.m[2] + m[2][3] * rhs.m[3];
				m[3] = m[3][0] * rhs.m[0] + m[3][1] * rhs.m[1] + m[3][2] * rhs.m[2] + m[3][3] * rhs.m[3];

				return *this;
			}


			Mat4d& operator/=(const value_type c)
			{
				m[0] /= c;
				m[1] /= c;
				m[2] /= c;
				m[3] /= c;
				return *this;
			}




			void Zero()
			{
				m[0].Zero();
				m[1].Zero();
				m[2].Zero();
				m[3].Zero();
			}

			void Identity()
			{
				m[0].x = value_type{ 1 };
				m[0].y = value_type{ 0 };
				m[0].z = value_type{ 0 };
				m[0].w = value_type{ 0 };

				m[1].x = value_type{ 0 };
				m[1].y = value_type{ 1 };
				m[1].z = value_type{ 0 };
				m[1].w = value_type{ 0 };

				m[2].x = value_type{ 0 };
				m[2].y = value_type{ 0 };
				m[2].z = value_type{ 1 };
				m[2].w = value_type{ 0 };

				m[3].x = value_type{ 0 };
				m[3].y = value_type{ 0 };
				m[3].z = value_type{ 0 };
				m[3].w = value_type{ 1 };
			}



			value_type Determinant() const
			{
				value_type determinant{ 0 };
				value_type s00 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
				value_type s01 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
				value_type s02 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
				value_type s03 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
				value_type s04 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
				value_type s05 = m[2][0] * m[3][1] - m[2][1] * m[3][0];

				determinant += m[0][0] * (m[1][1] * s00 - m[1][2] * s01 + m[1][3] * s02);
				determinant -= m[0][1] * (m[1][0] * s00 - m[1][2] * s03 + m[1][3] * s04);
				determinant += m[0][2] * (m[1][0] * s01 - m[1][1] * s03 + m[1][3] * s05);
				determinant -= m[0][3] * (m[1][0] * s02 - m[1][1] * s04 + m[1][2] * s05);

				return determinant;
			}


			Mat4d Inverse() const
			{
				Mat4d inverse;

				value_type s00 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
				value_type s01 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
				value_type s02 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
				value_type s03 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
				value_type s04 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
				value_type s05 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
				value_type s06 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
				value_type s07 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
				value_type s08 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
				value_type s09 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
				value_type s10 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
				value_type s11 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
				value_type s12 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
				value_type s13 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
				value_type s14 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
				value_type s15 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
				value_type s16 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
				value_type s17 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

				
				inverse.m[0][0] =  (m[1][1] * s00 - m[1][2] * s01 + m[1][3] * s02);
				inverse.m[0][1] = -(m[0][1] * s00 - m[0][2] * s01 + m[0][3] * s02);
				inverse.m[0][2] =  (m[0][1] * s06 - m[0][2] * s07 + m[0][3] * s08);
				inverse.m[0][3] = -(m[0][1] * s12 - m[0][2] * s13 + m[0][3] * s14);
				
				inverse.m[1][0] = -(m[1][0] * s00 - m[1][2] * s03 + m[1][3] * s04);
				inverse.m[1][1] =  (m[0][0] * s00 - m[0][2] * s03 + m[0][3] * s04);
				inverse.m[1][2] = -(m[0][0] * s06 - m[0][2] * s09 + m[0][3] * s10);
				inverse.m[1][3] =  (m[0][0] * s12 - m[0][2] * s15 + m[0][3] * s16);
				
				inverse.m[2][0] =  (m[1][0] * s01 - m[1][1] * s03 + m[1][3] * s05);
				inverse.m[2][1] = -(m[0][0] * s01 - m[0][1] * s03 + m[0][3] * s05);
				inverse.m[2][2] =  (m[0][0] * s07 - m[0][1] * s09 + m[0][3] * s11);
				inverse.m[2][3] = -(m[0][0] * s13 - m[0][1] * s15 + m[0][3] * s17);

				inverse.m[3][0] = -(m[1][0] * s02 - m[1][1] * s04 + m[1][2] * s05);
				inverse.m[3][1] =  (m[0][0] * s02 - m[0][1] * s04 + m[0][2] * s05);
				inverse.m[3][2] = -(m[0][0] * s08 - m[0][1] * s10 + m[0][2] * s11);
				inverse.m[3][3] =  (m[0][0] * s14 - m[0][1] * s16 + m[0][2] * s17);

				value_type d =	  m[0][0] * inverse.m[0][0] 
								+ m[0][1] * inverse.m[1][0] 
								+ m[0][2] * inverse.m[2][0] 
								+ m[0][3] * inverse.m[3][0];

				inverse /= d;

				return inverse;
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
				return std::format("{}\n{}\n{}\n{}", m[0].ToString(), m[1].ToString(), 
					m[2].ToString(), m[3].ToString());
			}

		private:
			row_t m[4];
		};


		/**************** TYPE ALIAS ************************/
		using Mat4df = Mat4d<real_t>;
		using Mat4di = Mat4d<integer_t>;
		/**************** TYPE ALIAS ************************/



		/*****************************************************************/
		//                  INLINE OPERATORS 
		/*****************************************************************/
		template <typename T>
		inline bool operator==(const Mat4d<T>& lhs, const Mat4d<T>& rhs)
		{
			return lhs(0) == rhs(0) && lhs(1) == rhs(1) && lhs(2) == rhs(2) && lhs(3) == rhs(3);
		}


		template <typename T>
		inline bool operator!=(const Mat4d<T>& lhs, const Mat4d<T>& rhs)
		{
			return !(lhs == rhs);
		}


		template <typename T>
		inline Mat4d<T> operator+(Mat4d<T> lhs, const Mat4d<T>& rhs)
		{
			lhs += rhs;
			return lhs;
		}


		template <typename T>
		inline Mat4d<T> operator-(Mat4d<T> lhs, const Mat4d<T>& rhs)
		{
			lhs -= rhs;
			return lhs;
		}


		template <typename T>
		inline Mat4d<T> operator*(Mat4d<T> lhs, const T c)
		{
			lhs *= c;
			return lhs;
		}


		template <typename T>
		inline Mat4d<T> operator/(Mat4d<T> lhs, const T c)
		{
			lhs /= c;
			return lhs;
		}


		template <typename T>
		inline Mat4d<T> operator*(Mat4d<T> lhs, const Mat4d<T>& rhs)
		{
			lhs *= rhs;
			return lhs;
		}


		template <typename T, typename U>
		inline Vec4d<std::common_type_t<T, U>> operator*(const Mat4d<T>& lhs, const Vec4d<U>& rhs)
		{
			using com_t = std::common_type_t<T, U>;
			com_t x = lhs(0).Dot(rhs);
			com_t y = lhs(1).Dot(rhs);
			com_t z = lhs(2).Dot(rhs);
			com_t w = lhs(3).Dot(rhs);
			return Vec4d<com_t>{x, y};
		}
	} //namespace Math
} //namespace Gargantua