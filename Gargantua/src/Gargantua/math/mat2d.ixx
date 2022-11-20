/*
gargantua/math/mat2d.ixx


PURPOSE: Matrix 2x2.


CLASSES:
	Mat2d: matrix 2x2 with row representation.

DESCRIPTION:
	The internal format used is row-major order. Consider that this is only relevant in terms of
	HOW operations are executed and not what they mean.
*/

export module gargantua.math.mat2d;

import <type_traits>;
import <string>;
import <format>;

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

		Mat2d(const T a, const T b, const T c, const T d) :
			m{ row_t{a, b}, row_t{c, d} }
		{

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
		auto operator()(const natural_t i) -> row_t
		{
			return m[i];
		}

		auto operator()(const natural_t i) const -> const row_t&
		{
			return m[i];
		}



		auto operator+=(const Mat2d& rhs) -> Mat2d&
		{
			m[0] += rhs.m[0];
			m[1] += rhs.m[1];
			return *this;
		}


		auto operator-=(const Mat2d& rhs) -> Mat2d&
		{
			m[0] -= rhs.m[0];
			m[1] -= rhs.m[1];
			return *this;
		}


		auto operator*=(const value_type c) -> Mat2d&
		{
			m[0] *= c;
			m[1] *= c;
			return *this;
		}


		auto operator*=(const Mat2d& rhs) -> Mat2d&
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


		auto operator/=(const T c) -> Mat2d&
		{
			m[0] /= c;
			m[1] /= c;
			return *this;
		}




		auto Zero() noexcept -> void
		{
			m[0].Zero();
			m[1].Zero();
		}

		auto Identity() noexcept -> void
		{
			m[0].x = T{ 1 };
			m[0].y = T{ 0 };

			m[1].x = T{ 0 };
			m[1].y = T{ 1 };
		}



		auto Determinant() const noexcept -> T
		{
			return m[0].x * m[1].y - m[0].y * m[1].x;
		}


		auto Inverse() const -> Mat2d
		{
			T d = Determinant();
			return Mat2d{ m[1][1] / d, -m[0][1] / d,
						-m[1][0] / d,  m[0][0] / d };
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
			return std::format("{}\n{}", m[0].ToString(), m[1].ToString());
		}

	private:
		row_t m[2];
	}; //class Mat2d


	/**************** TYPE ALIAS ************************/
	using Mat2df = Mat2d<real_t>;
	using mat2di = Mat2d<integer_t>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/
	template <typename T>
	inline auto operator==(const Mat2d<T>& lhs, const Mat2d<T>& rhs) -> bool
	{
		return lhs(0) == rhs(0) && lhs(1) == rhs(1);
	}


	template <typename T>
	inline auto operator!=(const Mat2d<T>& lhs, const Mat2d<T>& rhs) -> bool
	{
		return !(lhs == rhs);
	}


	template <typename T>
	inline auto operator+(Mat2d<T> lhs, const Mat2d<T>& rhs) -> Mat2d<T>
	{
		lhs += rhs;
		return lhs;
	}


	template <typename T>
	inline auto operator-(Mat2d<T> lhs, const Mat2d<T>& rhs) -> Mat2d<T>
	{
		lhs -= rhs;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator*(Mat2d<T> lhs, const U c) -> Mat2d<T>
	{
		lhs *= static_cast<U>(c);
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator/(Mat2d<T> lhs, const U c) -> Mat2d<T>
	{
		lhs /= static_cast<U>(c);
		return lhs;
	}


	template <typename T>
	inline auto operator*(Mat2d<T> lhs, const Mat2d<T>& rhs) -> Mat2d<T>
	{
		lhs *= rhs;
		return lhs;
	}


	template <typename T, typename U>
	inline auto operator*(const Mat2d<T>& lhs, const Vec2d<U>& rhs) -> Vec2d<std::common_type_t<T, U>>
	{
		using com_t = std::common_type_t<T, U>;
		com_t x = lhs(0).Dot(rhs);
		com_t y = lhs(1).Dot(rhs);
		return Vec2d<com_t>{x, y};
	}

} //namespace gargantua::math