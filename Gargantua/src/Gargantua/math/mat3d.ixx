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


		auto operator()(const u32 i, const u32 j) -> T&
		{
			return m[i][j];
		}

		auto operator()(const u32 i, const u32 j) const -> T
		{
			return m[i][j];
		}


		//return row i
		auto operator()(const u32 i) -> row_t&
		{
			return m[i];
		}

		auto operator()(const u32 i) const -> const row_t&
		{
			return m[i];
		}



		auto operator+=(const Mat3d& rhs) -> Mat3d&
		{
			m[0] += rhs.m[0];
			m[1] += rhs.m[1];
			m[2] += rhs.m[2];
			return *this;
		}


		auto operator-=(const Mat3d& rhs) -> Mat3d&
		{
			m[0] -= rhs.m[0];
			m[1] -= rhs.m[1];
			m[2] -= rhs.m[2];
			return *this;
		}


		auto operator*=(const T c) -> Mat3d&
		{
			m[0] *= c;
			m[1] *= c;
			m[2] *= c;
			return *this;
		}


		auto operator*=(const Mat3d& rhs) -> Mat3d&
		{
			m[0] = m[0][0] * rhs.m[0] + m[0][1] * rhs.m[1] + m[0][2] * rhs.m[2] + m[0][3] * rhs.m[3];
			m[1] = m[1][0] * rhs.m[0] + m[1][1] * rhs.m[1] + m[1][2] * rhs.m[2] + m[1][3] * rhs.m[3];
			m[2] = m[2][0] * rhs.m[0] + m[2][1] * rhs.m[1] + m[2][2] * rhs.m[2] + m[2][3] * rhs.m[3];

			return *this;
		}


		auto operator/=(const T c) -> Mat3d&
		{
			m[0] /= c;
			m[1] /= c;
			m[2] /= c;
			return *this;
		}



		auto Zero() -> void
		{
			m[0].Zero();
			m[1].Zero();
			m[2].Zero();
		}

		auto Identity() noexcept -> void
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



		auto Determinant() const noexcept -> T
		{
			T determinant{ 0 };
			determinant += m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
			determinant -= m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
			determinant += m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
			return determinant;
		}


		auto Inverse() const -> Mat3d
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


		auto GetAddress() const -> const T*
		{
			return &(m[0].x);
		}

		auto GetAddress() -> T*
		{
			return &(m[0].x);
		}


		auto ToString() const -> std::string
		{
			return std::format("{}\n{}\n{}", m[0].ToString(), m[1].ToString(),
				m[2].ToString());
		}

	private:
		row_t m[3];
	}; //class Mat3d


	/**************** TYPE ALIAS ************************/
	using Mat3di = Mat3d<i32>;
	using Mat3df = Mat3d<f32>;
	/**************** TYPE ALIAS ************************/



	/*****************************************************************/
	//                  INLINE OPERATORS 
	/*****************************************************************/
	template <typename T>
	inline auto operator==(const Mat3d<T>& lhs, const Mat3d<T>& rhs) -> bool
	{
		return lhs(0) == rhs(0) && lhs(1) == rhs(1) && lhs(2) == rhs(2) && lhs(3) == rhs(3);
	}


	template <typename T>
	inline auto operator!=(const Mat3d<T>& lhs, const Mat3d<T>& rhs) -> bool
	{
		return !(lhs == rhs);
	}


	template <typename T>
	inline auto operator+(Mat3d<T> lhs, const Mat3d<T>& rhs) -> Mat3d<T>
	{
		lhs += rhs;
		return lhs;
	}


	template <typename T>
	inline auto operator-(Mat3d<T> lhs, const Mat3d<T>& rhs) -> Mat3d<T>
	{
		lhs -= rhs;
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator*(Mat3d<T> lhs, const U c) -> Mat3d<T>
	{
		lhs *= static_cast<T>(c);
		return lhs;
	}


	template <typename T, typename U>
		requires std::is_arithmetic_v<U>
	inline auto operator/(Mat3d<T> lhs, const U c) -> Mat3d<T>
	{
		lhs /= static_cast<U>(c);
		return lhs;
	}


	template <typename T>
	inline auto operator*(Mat3d<T> lhs, const Mat3d<T>& rhs) -> Mat3d<T>
	{
		lhs *= rhs;
		return lhs;
	}


	template <typename T, typename U>
	inline auto operator*(const Mat3d<T>& lhs, const Vec3d<U>& rhs) -> Vec3d<std::common_type_t<T, U>>
	{
		using com_t = std::common_type_t<T, U>;
		com_t x = lhs(0).Dot(rhs);
		com_t y = lhs(1).Dot(rhs);
		com_t z = lhs(2).Dot(rhs);
		return Vec3d<com_t>{x, y, z};
	}

} //namespace gargantua::math