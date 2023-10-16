/*
* gargantua/math/mat2d.ixx
* 
* 
* PURPOSE: Matrix 2x2.
* 
* 
* CLASSES:
* 	Mat2d: matrix 2x2 with row representation.
* 
* DESCRIPTION:
* 	The internal format used is row-major order. Consider that this is only relevant in terms of
* 	HOW operations are executed and not what they mean.
* 	So for example C = A * B means that the matrix B is applied first and then A.
*/

export module gargantua.math.mat2d;

import <type_traits>;
import <string>;
import <format>;
import <compare>;
import <concepts>;

import gargantua.types;
import gargantua.math.vec2d;


export namespace gargantua::math
{

	template <typename T>
		requires std::is_arithmetic_v<T>
	class Mat2d
	{
	public:
		using value_type = T;
		using col_t = Vec2d<T>; //column type
		using row_t = Vec2d<T>; //row type

		constexpr Mat2d() noexcept = default;

		//Initialize the diagonal of the matrix with the value d
		constexpr Mat2d(const T& d) noexcept
		{
			m[0].x = d;
			m[1].y = d;
		}


		constexpr Mat2d(const row_t& row0, const row_t& row1) noexcept
		{
			m[0] = row0;
			m[1] = row1;
		}


		constexpr Mat2d(const T a, const T b, const T c, const T d) noexcept :
			m{ row_t{a, b}, row_t{c, d} }
		{

		}


		constexpr auto operator==(const Mat2d&) const -> bool = default;


		/*template <std::convertible_to<T> U>
		constexpr operator Mat2d<U>() const noexcept
		{
			return Mat2d<U>{ static_cast<Vec2d<U>>(m[0]), static_cast<Vec2d<U>>(m[1]) };
		}*/


		// TODO: use multidimensional operator []
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
		constexpr auto operator()(const u32 i) -> row_t
		{
			return m[i];
		}


		[[nodiscard]]
		constexpr auto operator()(const u32 i) const -> const row_t&
		{
			return m[i];
		}


		constexpr auto operator+=(const Mat2d& rhs) noexcept -> Mat2d&
		{
			m[0] += rhs.m[0];
			m[1] += rhs.m[1];
			return *this;
		}


		constexpr auto operator-=(const Mat2d& rhs) noexcept -> Mat2d&
		{
			m[0] -= rhs.m[0];
			m[1] -= rhs.m[1];
			return *this;
		}


		constexpr auto operator*=(const T c) noexcept -> Mat2d&
		{
			m[0] *= c;
			m[1] *= c;
			return *this;
		}


		constexpr auto operator*=(const Mat2d& rhs) noexcept -> Mat2d&
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


		constexpr auto operator/=(const T c) -> Mat2d&
		{
			m[0] /= c;
			m[1] /= c;
			return *this;
		}

		
		constexpr auto Zero() noexcept -> void
		{
			m[0].Zero();
			m[1].Zero();
		}


		constexpr auto Identity() noexcept -> void
		{
			m[0].x = T{ 1 };
			m[0].y = T{ 0 };

			m[1].x = T{ 0 };
			m[1].y = T{ 1 };
		}


		[[nodiscard]]
		constexpr auto Determinant() const noexcept -> T
		{
			return m[0].x * m[1].y - m[0].y * m[1].x;
		}


		// Precondition: Determinant is != 0.
		[[nodiscard]]
		constexpr auto Inverse() const -> Mat2d
		{
			auto d = Determinant();
			return Mat2d{ m[1][1] / d, -m[0][1] / d,
						-m[1][0] / d,  m[0][0] / d };
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
			return std::format("{}\n{}", m[0].ToString(), m[1].ToString());
		}

	private:
		row_t m[2];
	}; 


	/**************** TYPE ALIAS ************************/
	using Mat2di = Mat2d<i32>;
	using Mat2df = Mat2d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/


	template <typename T>
	[[nodiscard]]
	constexpr auto operator+(const Mat2d<T>& lhs, const Mat2d<T>& rhs) noexcept -> Mat2d<T>
	{
		return { lhs(0) + rhs(0), lhs(1) + rhs(1) };
	}


	template <typename T>
	[[nodiscard]]
	constexpr auto operator-(const Mat2d<T>& lhs, const Mat2d<T>& rhs) noexcept -> Mat2d<T>
	{
		return { lhs(0) - rhs(0), lhs(1) - rhs(1) };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator*(Mat2d<T> lhs, const U c) -> Mat2d<decltype(lhs.m[0].x * c)>
	{
		return { lhs(0) * c, lhs(1) * c };
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	[[nodiscard]]
	constexpr auto operator/(const Mat2d<T>& lhs, const U c) -> Mat2d<decltype(lhs.m[0].x / c)>
	{
		return { lhs(0) / c, lhs(1) / c };
	}


	template <typename T>
	[[nodiscard]]
	constexpr auto operator*(Mat2d<T> lhs, const Mat2d<T>& rhs) noexcept -> Mat2d<T>
	{
		lhs *= rhs;
		return lhs;
	}


	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator*(const Mat2d<T>& lhs, const Vec2d<U>& rhs) noexcept -> Vec2d<decltype(lhs(0).x* rhs.x)>
	{
		return { lhs(0).Dot(rhs), lhs(1).Dot(rhs) };
	}

} //namespace gargantua::math