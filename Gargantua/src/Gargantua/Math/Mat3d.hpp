#pragma once
/*
Gargantua/Math/Mat3d.hpp


PURPOSE: Matrix 4x4.


CLASSES:
	Mat3d: matrix 4x4 with row representation.

DESCRIPTION:
	The internal format used is row-major order. Consider that this is only relevant in terms of
	HOW operations are executed and not what they mean.

	The Inverse and the Determinant are calculated by writing the explicit formula based on cofactors.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec3d.hpp"

#include <type_traits>
#include <string>
#include <format>

namespace Gargantua
{
	namespace Math
	{
		template <typename T>
			requires std::is_arithmetic_v<T>
		class Mat3d
		{
		public:
			using value_type = T;
			using col_t = Vec3d<T>; //column type
			using row_t = Vec3d<T>; //row type

			Mat3d() = default;

			//Initialize the diagonal of the matrix with the value d
			Mat3d(const T& d)
			{
				m[0][0] = d;
				m[1][1] = d;
				m[2][2] = d;
			}

			Mat3d(row_t row0, row_t row1, row_t row2)
			{
				m[0] = std::move(row0);
				m[1] = std::move(row1);
				m[2] = std::move(row2);
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



			Mat3d& operator+=(const Mat3d& rhs)
			{
				m[0] += rhs.m[0];
				m[1] += rhs.m[1];
				m[2] += rhs.m[2];
				return *this;
			}


			Mat3d& operator-=(const Mat3d& rhs)
			{
				m[0] -= rhs.m[0];
				m[1] -= rhs.m[1];
				m[2] -= rhs.m[2];
				return *this;
			}


			Mat3d& operator*=(const value_type c)
			{
				m[0] *= c;
				m[1] *= c;
				m[2] *= c;
				return *this;
			}


			Mat3d& operator*=(const Mat3d& rhs)
			{
				m[0] = m[0][0] * rhs.m[0] + m[0][1] * rhs.m[1] + m[0][2] * rhs.m[2] + m[0][3] * rhs.m[3];
				m[1] = m[1][0] * rhs.m[0] + m[1][1] * rhs.m[1] + m[1][2] * rhs.m[2] + m[1][3] * rhs.m[3];
				m[2] = m[2][0] * rhs.m[0] + m[2][1] * rhs.m[1] + m[2][2] * rhs.m[2] + m[2][3] * rhs.m[3];

				return *this;
			}


			Mat3d& operator/=(const value_type c)
			{
				m[0] /= c;
				m[1] /= c;
				m[2] /= c;
				return *this;
			}



			void Zero()
			{
				m[0].Zero();
				m[1].Zero();
				m[2].Zero();
			}

			void Identity()
			{
				m[0].x = value_type{ 1 };
				m[0].y = value_type{ 0 };
				m[0].z = value_type{ 0 };

				m[1].x = value_type{ 0 };
				m[1].y = value_type{ 1 };
				m[1].z = value_type{ 0 };

				m[2].x = value_type{ 0 };
				m[2].y = value_type{ 0 };
				m[2].z = value_type{ 1 };
			}



			value_type Determinant() const
			{
				value_type determinant{ 0 };
				determinant += m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
				determinant -= m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
				determinant += m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
				return determinant;
			}


			Mat3d Inverse() const
			{
				value_type d = Determinant();
				
				Mat3d inverse;

				inverse.m[0][0] =  m[1][1] * m[2][2] - m[1][2] * m[2][1];
				inverse.m[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);
				inverse.m[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
					  
				inverse.m[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]);
				inverse.m[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
				inverse.m[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]);
					   
				inverse.m[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
				inverse.m[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]);
				inverse.m[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

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
				return std::format("{}\n{}\n{}", m[0].ToString(), m[1].ToString(),
					m[2].ToString());
			}

		private:
			row_t m[3];
		};


		/**************** TYPE ALIAS ************************/
		using Mat3df = Mat3d<real_t>;
		using Mat3di = Mat3d<integer_t>;
		/**************** TYPE ALIAS ************************/



		/*****************************************************************/
		//                  INLINE OPERATORS 
		/*****************************************************************/
		template <typename T>
		inline bool operator==(const Mat3d<T>& lhs, const Mat3d<T>& rhs)
		{
			return lhs(0) == rhs(0) && lhs(1) == rhs(1) && lhs(2) == rhs(2) && lhs(3) == rhs(3);
		}


		template <typename T>
		inline bool operator!=(const Mat3d<T>& lhs, const Mat3d<T>& rhs)
		{
			return !(lhs == rhs);
		}


		template <typename T>
		inline Mat3d<T> operator+(Mat3d<T> lhs, const Mat3d<T>& rhs)
		{
			lhs += rhs;
			return lhs;
		}


		template <typename T>
		inline Mat3d<T> operator-(Mat3d<T> lhs, const Mat3d<T>& rhs)
		{
			lhs -= rhs;
			return lhs;
		}


		template <typename T>
		inline Mat3d<T> operator*(Mat3d<T> lhs, const T c)
		{
			lhs *= c;
			return lhs;
		}


		template <typename T>
		inline Mat3d<T> operator/(Mat3d<T> lhs, const T c)
		{
			lhs /= c;
			return lhs;
		}


		template <typename T>
		inline Mat3d<T> operator*(Mat3d<T> lhs, const Mat3d<T>& rhs)
		{
			lhs *= rhs;
			return lhs;
		}


		template <typename T, typename U>
		inline Vec3d<std::common_type_t<T, U>> operator*(const Mat3d<T>& lhs, const Vec3d<U>& rhs)
		{
			using com_t = std::common_type_t<T, U>;
			com_t x = lhs(0).Dot(rhs);
			com_t y = lhs(1).Dot(rhs);
			com_t z = lhs(2).Dot(rhs);
			com_t w = lhs(3).Dot(rhs);
			return Vec3d<com_t>{x, y};
		}
	} //namespace Math
} //namespace Gargantua