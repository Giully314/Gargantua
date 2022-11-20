/*
gargantua/math/mat4d.ixx


PURPOSE: Matrix 4x4.


CLASSES:
	Mat4d: matrix 4x4 with row representation.

DESCRIPTION:
	The internal format used is row-major order. Consider that this is only relevant in terms of
	HOW operations are executed and not what they mean.

	The Inverse and the Determinant are calculated by writing the explicit formula based on cofactors.

TODO:
	is the static variable dim necessary?
	
*/

export module gargantua.math.mat4d;

import <type_traits>;
import <string>;
import <format>;

import gargantua.types;
import gargantua.math.vec4d;


export namespace gargantua::math
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


		auto operator()(const natural_t i, const natural_t j) -> T&
		{
			return m[i][j];
		}

		auto operator()(const natural_t i, const natural_t j) const -> T
		{
			return m[i][j];
		}


		//return row i
		auto operator()(const natural_t i) -> row_t&
		{
			return m[i];
		}

		auto operator()(const natural_t i) const -> const row_t&
		{
			return m[i];
		}



		auto operator+=(const Mat4d& rhs) -> Mat4d&
		{
			m[0] += rhs.m[0];
			m[1] += rhs.m[1];
			m[2] += rhs.m[2];
			m[3] += rhs.m[3];
			return *this;
		}


		auto operator-=(const Mat4d& rhs) -> Mat4d&
		{
			m[0] -= rhs.m[0];
			m[1] -= rhs.m[1];
			m[2] -= rhs.m[2];
			m[3] -= rhs.m[3];
			return *this;
		}


		auto operator*=(const T c) -> Mat4d&
		{
			m[0] *= c;
			m[1] *= c;
			m[2] *= c;
			m[3] *= c;
			return *this;
		}


		auto operator*=(const Mat4d& rhs) -> Mat4d&
		{
			m[0] = m[0][0] * rhs.m[0] + m[0][1] * rhs.m[1] + m[0][2] * rhs.m[2] + m[0][3] * rhs.m[3];
			m[1] = m[1][0] * rhs.m[0] + m[1][1] * rhs.m[1] + m[1][2] * rhs.m[2] + m[1][3] * rhs.m[3];
			m[2] = m[2][0] * rhs.m[0] + m[2][1] * rhs.m[1] + m[2][2] * rhs.m[2] + m[2][3] * rhs.m[3];
			m[3] = m[3][0] * rhs.m[0] + m[3][1] * rhs.m[1] + m[3][2] * rhs.m[2] + m[3][3] * rhs.m[3];

			return *this;
		}


		auto operator/=(const T c) -> Mat4d&
		{
			m[0] /= c;
			m[1] /= c;
			m[2] /= c;
			m[3] /= c;
			return *this;
		}




		auto Zero() noexcept -> void
		{
			m[0].Zero();
			m[1].Zero();
			m[2].Zero();
			m[3].Zero();
		}

		auto Identity() noexcept -> void
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



		auto Determinant() const noexcept -> void
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


		auto Inverse() const -> Mat4d
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


		auto GetAddress() const -> const T*
		{
			return &(m[0].x);
		}

		auto GetAddress() -> T*
		{
			return &(m[0].x);
		}


		auto ToString() -> std::string
		{
			return std::format("{}\n{}\n{}\n{}", m[0].ToString(), m[1].ToString(),
				m[2].ToString(), m[3].ToString());
		}

	private:
		row_t m[4];
	}; //class Mat4d


	/**************** TYPE ALIAS ************************/
	using Mat4df = Mat4d<real_t>;
	using Mat4di = Mat4d<integer_t>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/
	template <typename T>
	inline auto operator==(const Mat4d<T>& lhs, const Mat4d<T>& rhs) -> bool
	{
		return lhs(0) == rhs(0) && lhs(1) == rhs(1) && lhs(2) == rhs(2) && lhs(3) == rhs(3);
	}


	template <typename T>
	inline auto operator!=(const Mat4d<T>& lhs, const Mat4d<T>& rhs) -> bool
	{
		return !(lhs == rhs);
	}


	template <typename T>
	inline auto operator+(Mat4d<T> lhs, const Mat4d<T>& rhs) -> Mat4d<T>
	{
		lhs += rhs;
		return lhs;
	}


	template <typename T>
	inline auto operator-(Mat4d<T> lhs, const Mat4d<T>& rhs) -> Mat4d<T>
	{
		lhs -= rhs;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator*(Mat4d<T> lhs, const T c) -> Mat4d<T>
	{
		lhs *= static_cast<T>(c);
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator/(Mat4d<T> lhs, const U c) -> Mat4d<T>
	{
		lhs /= static_cast<T>(c);
		return lhs;
	}


	template <typename T>
	inline auto operator*(Mat4d<T> lhs, const Mat4d<T>& rhs) -> Mat4d<T>
	{
		lhs *= rhs;
		return lhs;
	}


	template <typename T, typename U>
	inline auto operator*(const Mat4d<T>& lhs, const Vec4d<U>& rhs) -> Vec4d<std::common_type_t<T, U>>
	{
		using com_t = std::common_type_t<T, U>;
		com_t x = lhs(0).Dot(rhs);
		com_t y = lhs(1).Dot(rhs);
		com_t z = lhs(2).Dot(rhs);
		com_t w = lhs(3).Dot(rhs);
		return Vec4d<com_t>{x, y};
	}

} //namespace gargantua::math
