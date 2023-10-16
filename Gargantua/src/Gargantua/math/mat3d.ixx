/*
* gargantua/math/mat3d.ixx
* 
* 
* PURPOSE: Matrix 3x3.
* 
* 
* CLASSES:
* 	Mat3d: matrix 3x3 with row representation.
* 
* DESCRIPTION:
* 	The internal format used is row-major order. Consider that this is only relevant in terms of
* 	HOW operations are executed and not what they mean.
* 	So for example C = A * B means that the matrix B is applied first and then A.
* 
* 	The Inverse and the Determinant are calculated by writing the explicit formula based on cofactors.
*/

export module gargantua.math.mat3d;

import <type_traits>;
import <string>;
import <format>;
import <compare>;

import gargantua.types;
import gargantua.math.vec3d;


export namespace gargantua::math
{

	template <typename T>
		requires std::is_arithmetic_v<T>
	class Mat3d
	{
	public:
		using value_type = T;
		using col_t = Vec3d<T>; //column type
		using row_t = Vec3d<T>; //row type

		constexpr Mat3d() noexcept = default;

		//Initialize the diagonal of the matrix with the value d
		constexpr Mat3d(const T& d) noexcept
		{
			m[0][0] = d;
			m[1][1] = d;
			m[2][2] = d;
		}


		constexpr Mat3d(const row_t& row0, const row_t& row1, const row_t& row2) noexcept 
		{
			m[0] = row0;
			m[1] = row1;
			m[2] = row2;
		}


		constexpr auto operator==(const Mat3d&) const -> bool = default;

		
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


		// return row i
		[[nodiscard]]
		constexpr auto operator()(const u32 i) -> row_t&
		{
			return m[i];
		}


		// return row i
		[[nodiscard]]
		constexpr auto operator()(const u32 i) const -> const row_t&
		{
			return m[i];
		}



		constexpr auto operator+=(const Mat3d& rhs) noexcept -> Mat3d&
		{
			m[0] += rhs.m[0];
			m[1] += rhs.m[1];
			m[2] += rhs.m[2];
			return *this;
		}


		constexpr auto operator-=(const Mat3d& rhs) noexcept -> Mat3d&
		{
			m[0] -= rhs.m[0];
			m[1] -= rhs.m[1];
			m[2] -= rhs.m[2];
			return *this;
		}


		constexpr auto operator*=(const T c) noexcept -> Mat3d&
		{
			m[0] *= c;
			m[1] *= c;
			m[2] *= c;
			return *this;
		}


		constexpr auto operator*=(const Mat3d& rhs) noexcept -> Mat3d&
		{
			m[0] = m[0][0] * rhs.m[0] + m[0][1] * rhs.m[1] + m[0][2] * rhs.m[2] + m[0][3] * rhs.m[3];
			m[1] = m[1][0] * rhs.m[0] + m[1][1] * rhs.m[1] + m[1][2] * rhs.m[2] + m[1][3] * rhs.m[3];
			m[2] = m[2][0] * rhs.m[0] + m[2][1] * rhs.m[1] + m[2][2] * rhs.m[2] + m[2][3] * rhs.m[3];

			return *this;
		}


		constexpr auto operator/=(const T c) -> Mat3d&
		{
			m[0] /= c;
			m[1] /= c;
			m[2] /= c;
			return *this;
		}


		constexpr auto Zero() noexcept -> void
		{
			m[0].Zero();
			m[1].Zero();
			m[2].Zero();
		}


		constexpr auto Identity() noexcept -> void
		{
			m[0].x = T{ 1 };
			m[0].y = T{ 0 };
			m[0].z = T{ 0 };

			m[1].x = T{ 0 };
			m[1].y = T{ 1 };
			m[1].z = T{ 0 };

			m[2].x = T{ 0 };
			m[2].y = T{ 0 };
			m[2].z = T{ 1 };
		}


		[[nodiscard]]
		constexpr auto Determinant() const noexcept -> T
		{
			T determinant{ 0 };
			determinant += m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
			determinant -= m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
			determinant += m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
			return determinant;
		}


		// Precondition: Determinant() != 0.
		[[nodiscard]]
		constexpr auto Inverse() const -> Mat3d
		{
			T d = Determinant();

			Mat3d inverse;

			inverse.m[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
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
			return std::format("{}\n{}\n{}", m[0].ToString(), m[1].ToString(),
				m[2].ToString());
		}

	private:
		row_t m[3];
	}; 


	/**************** TYPE ALIAS ************************/
	using Mat3di = Mat3d<i32>;
	using Mat3df = Mat3d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/


	template <typename T>
	[[nodiscard]]
	constexpr auto operator+(const Mat3d<T>& lhs, const Mat3d<T>& rhs) noexcept -> Mat3d<T>
	{
		return { lhs(0) + rhs(0), lhs(1) + rhs(1), lhs(2) + rhs(2) };
	}


	template <typename T>
	[[nodiscard]]
	constexpr auto operator-(const Mat3d<T>& lhs, const Mat3d<T>& rhs) noexcept -> Mat3d<T>
	{
		return { lhs(0) - rhs(0), lhs(1) - rhs(1), lhs(2) - rhs(2) };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator*(const Mat3d<T>& lhs, const U c) noexcept -> Mat3d<decltype(lhs(0).x * c)>
	{
		return { lhs(0) * c, lhs(1) * c, lhs(2) * c };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator/(const Mat3d<T>& lhs, const U c) -> Mat3d<decltype(lhs(0).x* c)>
	{
		return { lhs(0) / c, lhs(1) / c, lhs(2) / c };
	}


	template <typename T>
	[[nodiscard]]
	constexpr auto operator*(Mat3d<T> lhs, const Mat3d<T>& rhs) noexcept -> Mat3d<T>
	{
		lhs *= rhs;
		return lhs;
	}


	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator*(const Mat3d<T>& lhs, const Vec3d<U>& rhs) noexcept -> Vec3d<decltype(lhs(0).x * rhs.x)>
	{
		return { lhs(0).Dot(rhs), lhs(1).Dot(rhs), lhs(2).Dot(rhs) };
	}

} //namespace gargantua::math