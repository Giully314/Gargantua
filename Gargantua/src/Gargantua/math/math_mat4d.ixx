/*
* gargantua/math/math_mat4d.ixx
* 
* 
* PURPOSE: Matrix 4x4.
* 
* 
* CLASSES:
* 	Mat4d: matrix 4x4 with row representation.
* 
* DESCRIPTION:
* 	The internal format used is row-major order. Consider that this is only relevant in terms of
* 	HOW operations are executed and not what they mean.
* 	So for example C = A * B means that the matrix B is applied first and then A.
* 
* 	The Inverse and the Determinant are calculated by writing the explicit formula based on cofactors.
* 	
*/

export module gargantua.math.mat4d;

import <type_traits>;
import <string>;
import <format>;
import <compare>;
import <concepts>;

import gargantua.types;
import gargantua.math.concepts;
import gargantua.math.vec4d;


export namespace gargantua::math
{
	template <CIsArithmetic T>
	class Mat4d
	{
	public:
		using value_type = T;
		using col_t = Vec4d<T>; //column type
		using row_t = Vec4d<T>; //row type

		constexpr explicit Mat4d() noexcept = default;

		//Initialize the diagonal of the matrix with the value d
		constexpr explicit Mat4d(const T& d) noexcept
		{
			m[0][0] = d;
			m[1][1] = d;
			m[2][2] = d;
			m[3][3] = d;
		}


		constexpr explicit Mat4d(const row_t& row0, const row_t& row1, const row_t& row2, const row_t& row3) noexcept 
		{
			m[0] = row0;
			m[1] = row1;
			m[2] = row2;
			m[3] = row3;
		}


		constexpr auto operator==(const Mat4d&) const noexcept -> bool = default;


		template <std::convertible_to<T> U>
		constexpr explicit operator Mat4d<U>() const noexcept
		{
			return Mat4d<U>{ static_cast<Vec4d<U>>(m[0]),
				static_cast<Vec4d<U>>(m[1]),
				static_cast<Vec4d<U>>(m[2]),
				static_cast<Vec4d<U>>(m[3]) };
		}


		[[nodiscard]]
		constexpr auto operator()(const u32 i, const u32 j) -> T&
		{
			return m[i][j];
		}


		[[nodiscard]]
		constexpr auto operator()(const u32 i, const u32 j) const -> T
		{
			return m[i][j];
		}


		//return row i
		[[nodiscard]]
		constexpr auto operator()(const u32 i) -> row_t&
		{
			return m[i];
		}


		[[nodiscard]]
		constexpr auto operator()(const u32 i) const -> const row_t&
		{
			return m[i];
		}


		constexpr auto operator+=(const Mat4d& rhs) noexcept -> Mat4d&
		{
			m[0] += rhs.m[0];
			m[1] += rhs.m[1];
			m[2] += rhs.m[2];
			m[3] += rhs.m[3];
			return *this;
		}


		constexpr auto operator-=(const Mat4d& rhs) noexcept -> Mat4d&
		{
			m[0] -= rhs.m[0];
			m[1] -= rhs.m[1];
			m[2] -= rhs.m[2];
			m[3] -= rhs.m[3];
			return *this;
		}


		constexpr auto operator*=(const T c) noexcept -> Mat4d&
		{
			m[0] *= c;
			m[1] *= c;
			m[2] *= c;
			m[3] *= c;
			return *this;
		}


		constexpr auto operator*=(const Mat4d& rhs) noexcept -> Mat4d&
		{
			m[0] = m[0][0] * rhs.m[0] + m[0][1] * rhs.m[1] + m[0][2] * rhs.m[2] + m[0][3] * rhs.m[3];
			m[1] = m[1][0] * rhs.m[0] + m[1][1] * rhs.m[1] + m[1][2] * rhs.m[2] + m[1][3] * rhs.m[3];
			m[2] = m[2][0] * rhs.m[0] + m[2][1] * rhs.m[1] + m[2][2] * rhs.m[2] + m[2][3] * rhs.m[3];
			m[3] = m[3][0] * rhs.m[0] + m[3][1] * rhs.m[1] + m[3][2] * rhs.m[2] + m[3][3] * rhs.m[3];

			return *this;
		}


		constexpr auto operator/=(const T c) -> Mat4d&
		{
			m[0] /= c;
			m[1] /= c;
			m[2] /= c;
			m[3] /= c;
			return *this;
		}


		constexpr auto Zero() noexcept -> void
		{
			m[0].Zero();
			m[1].Zero();
			m[2].Zero();
			m[3].Zero();
		}

		constexpr auto Identity() noexcept -> void
		{
			m[0].x = T{ 1 };
			m[0].y = T{ 0 };
			m[0].z = T{ 0 };
			m[0].w = T{ 0 };

			m[1].x = T{ 0 };
			m[1].y = T{ 1 };
			m[1].z = T{ 0 };
			m[1].w = T{ 0 };

			m[2].x = T{ 0 };
			m[2].y = T{ 0 };
			m[2].z = T{ 1 };
			m[2].w = T{ 0 };

			m[3].x = T{ 0 };
			m[3].y = T{ 0 };
			m[3].z = T{ 0 };
			m[3].w = T{ 1 };
		}


		[[nodiscard]]
		constexpr auto Determinant() const noexcept -> T
		{
			T determinant{ 0 };
			T s00 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
			T s01 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
			T s02 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
			T s03 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
			T s04 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
			T s05 = m[2][0] * m[3][1] - m[2][1] * m[3][0];

			determinant += m[0][0] * (m[1][1] * s00 - m[1][2] * s01 + m[1][3] * s02);
			determinant -= m[0][1] * (m[1][0] * s00 - m[1][2] * s03 + m[1][3] * s04);
			determinant += m[0][2] * (m[1][0] * s01 - m[1][1] * s03 + m[1][3] * s05);
			determinant -= m[0][3] * (m[1][0] * s02 - m[1][1] * s04 + m[1][2] * s05);

			return determinant;
		}


		[[nodiscard]]
		constexpr auto Inverse() const -> Mat4d
		{
			Mat4d inverse;

			T s00 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
			T s01 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
			T s02 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
			T s03 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
			T s04 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
			T s05 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
			T s06 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
			T s07 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
			T s08 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
			T s09 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
			T s10 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
			T s11 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
			T s12 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
			T s13 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
			T s14 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
			T s15 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
			T s16 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
			T s17 = m[1][0] * m[2][1] - m[1][1] * m[2][0];


			inverse.m[0][0] = (m[1][1] * s00 - m[1][2] * s01 + m[1][3] * s02);
			inverse.m[0][1] = -(m[0][1] * s00 - m[0][2] * s01 + m[0][3] * s02);
			inverse.m[0][2] = (m[0][1] * s06 - m[0][2] * s07 + m[0][3] * s08);
			inverse.m[0][3] = -(m[0][1] * s12 - m[0][2] * s13 + m[0][3] * s14);

			inverse.m[1][0] = -(m[1][0] * s00 - m[1][2] * s03 + m[1][3] * s04);
			inverse.m[1][1] = (m[0][0] * s00 - m[0][2] * s03 + m[0][3] * s04);
			inverse.m[1][2] = -(m[0][0] * s06 - m[0][2] * s09 + m[0][3] * s10);
			inverse.m[1][3] = (m[0][0] * s12 - m[0][2] * s15 + m[0][3] * s16);

			inverse.m[2][0] = (m[1][0] * s01 - m[1][1] * s03 + m[1][3] * s05);
			inverse.m[2][1] = -(m[0][0] * s01 - m[0][1] * s03 + m[0][3] * s05);
			inverse.m[2][2] = (m[0][0] * s07 - m[0][1] * s09 + m[0][3] * s11);
			inverse.m[2][3] = -(m[0][0] * s13 - m[0][1] * s15 + m[0][3] * s17);

			inverse.m[3][0] = -(m[1][0] * s02 - m[1][1] * s04 + m[1][2] * s05);
			inverse.m[3][1] = (m[0][0] * s02 - m[0][1] * s04 + m[0][2] * s05);
			inverse.m[3][2] = -(m[0][0] * s08 - m[0][1] * s10 + m[0][2] * s11);
			inverse.m[3][3] = (m[0][0] * s14 - m[0][1] * s16 + m[0][2] * s17);

			value_type d = m[0][0] * inverse.m[0][0]
				+ m[0][1] * inverse.m[1][0]
				+ m[0][2] * inverse.m[2][0]
				+ m[0][3] * inverse.m[3][0];

			inverse /= d;

			return inverse;
		}


		[[nodiscard]]
		constexpr auto GetAddress() const noexcept -> const T*
		{
			return &(m[0].x);
		}


		[[nodiscard]]
		constexpr auto GetAddress() noexcept -> T*
		{
			return &(m[0].x);
		}


		[[nodiscard]]
		constexpr auto ToString() const -> std::string
		{
			return std::format("{}\n{}\n{}\n{}", m[0].ToString(), m[1].ToString(),
				m[2].ToString(), m[3].ToString());
		}

	private:
		row_t m[4];
	}; 


	/**************** TYPE ALIAS ************************/
	using Mat4di = Mat4d<i32>;
	using Mat4df = Mat4d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator+(const Mat4d<T>& lhs, const Mat4d<T>& rhs) noexcept -> Mat4d<T>
	{
		return Mat4d<T>{ lhs(0) + rhs(0), lhs(1) + rhs(1), lhs(2) + rhs(2), lhs(3) + rhs(3) };
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator-(Mat4d<T> lhs, const Mat4d<T>& rhs) noexcept -> Mat4d<T>
	{
		return Mat4d<T>{ lhs(0) - rhs(0), lhs(1) - rhs(1), lhs(2) - rhs(2), lhs(3) - rhs(3) };
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator*(Mat4d<T> lhs, const T c) noexcept -> Mat4d<T>
	{
		return Mat4d<T>{ lhs(0) * c, lhs(1) * c, lhs(2) * c, lhs(3) * c };
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator/(Mat4d<T> lhs, const T c) -> Mat4d<T>
	{
		return Mat4d<T>{ lhs(0) / c, lhs(1) / c, lhs(2) / c, lhs(3) / c };
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator*(Mat4d<T> lhs, const Mat4d<T>& rhs) noexcept -> Mat4d<T>
	{
		lhs *= rhs;
		return lhs;
	}


	template <CIsArithmetic T>
	[[nodiscard]]
	constexpr auto operator*(const Mat4d<T>& lhs, const Vec4d<T>& rhs) noexcept -> Vec4d<T>
	{
		return Vec4d<T>{ lhs(0).Dot(rhs), lhs(1).Dot(rhs), lhs(2).Dot(rhs), lhs(3).Dot(rhs) };
	}

} //namespace gargantua::math
