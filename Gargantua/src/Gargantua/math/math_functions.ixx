/*
* gargantua/math/functions.ixx
* 
* PURPOSE: Mathematical functions for different purposes.
* 
* CLASSES:
* 	Projection: Provide functions for projections.
* 	Transform3d: Provide functions for 3d transformations. (really temporary, not so much useful for a 2d engine)
* 	Transform2d: Functions for 2d transformations.
* 	Angles: Conversion between angles.
* 
* DESCRIPTION:
*	Utility math functions.
*/

export module gargantua.math.math_functions;

import <cmath>;
import <numbers>;
import <type_traits>;
import <concepts>;

import gargantua.types;
import gargantua.math.vector;
import gargantua.math.matrix;


namespace gargantua::math
{
	template <typename T>
	concept Number = std::is_arithmetic_v<T>;

	export 
	struct Product
	{
		template <Number T>
		[[nodiscard]]
		static constexpr auto Dot(const Vec2d<T>& v1, const Vec2d<T>& v2) noexcept -> T
		{
			return v1.Dot(v2);
		}


		template <Number T>
		[[nodiscard]]
		static constexpr auto Hadamard(const Vec2d<T>& v1, const Vec2d<T>& v2) noexcept -> Vec2d<T>
		{
			return { v1.x * v2.x, v1.y * v2.y };
		}


		template <Number T>
		[[nodiscard]]
		static constexpr auto Cross(const Vec2d<T>& v1, const Vec2d<T>& v2) noexcept -> T
		{
			return v1.x * v2.y - v1.y * v2.x;
		}
	};



	//*********************** PROJECTION *********************************************
	export
	struct Projection
	{

		// https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix
		template <Number T>
		[[nodiscard]]
		static constexpr auto Orthographic(const T l, const T b, const T r, const T t, 
											const T n, const T f) -> Mat4d<T>
		{
			Mat4d<T> ortho;

			ortho(0, 0) = static_cast<T>(2) / (r - l);
			ortho(0, 3) = -(r + l) / (r - l);

			ortho(1, 1) = static_cast<T>(2) / (t - b);
			ortho(1, 3) = -(t + b) / (t - b);

			ortho(2, 2) = -static_cast<T>(2) / (f - n);
			ortho(2, 3) = -(f + n) / (f - n);

			ortho(3, 3) = static_cast<T>(1);

			return ortho;
		}


		template <Number T>
		[[nodiscard]]
		static constexpr auto Orthographic(const T l, const T b, const T r, const T t) -> Mat4d<T>
		{
			Mat4d<T> ortho;

			ortho(0, 0) = static_cast<T>(2) / (r - l);
			ortho(0, 3) = -(r + l) / (r - l);

			ortho(1, 1) = static_cast<T>(2) / (t - b);
			ortho(1, 3) = -(t + b) / (t - b);

			ortho(2, 2) = -static_cast<T>(1);

			ortho(3, 3) = static_cast<T>(1);

			return ortho;
		}
	};

	//*********************** PROJECTION *********************************************



	//*********************** TRANSFORM 3D *****************************************
	export
	struct Transform3d
	{
		template <Number T>
		[[nodiscard]]
		static constexpr auto Translate(const Vec3d<T>& v) noexcept -> Mat4d<T>
		{
			Mat4d<T> translation;

			translation(0, 0) = static_cast<T>(1);
			translation(0, 3) = v.x;

			translation(1, 1) = static_cast<T>(1);
			translation(1, 3) = v.y;

			translation(2, 2) = static_cast<T>(1);
			translation(2, 3) = v.z;

			translation(3, 3) = static_cast<T>(1);

			return translation;
		}

		/*Angle in radians*/
		template <Number T>
		[[nodiscard]]
		static constexpr auto RotateZ(const T a) noexcept -> Mat4d<T>
		{
			T c = std::cos(a);
			T s = std::sin(a);
			Mat4d<T> rotation;

			rotation(0, 0) = c;
			rotation(0, 1) = -s;

			rotation(1, 0) = s;
			rotation(1, 1) = c;

			rotation(2, 2) = static_cast<T>(1);

			rotation(3, 3) = static_cast<T>(1);

			return rotation;
		}


		template <Number T>
		[[nodiscard]]
		static constexpr auto Scale(const T c) noexcept -> Mat4d<T>
		{
			Mat4d<T> scale{ c };

			scale(3, 3) = static_cast<T>(1);

			return scale;
		}


		template <Number T>
		[[nodiscard]]
		static constexpr auto Scale(const Vec3d<T>& v) noexcept -> Mat4d<T>
		{
			Mat4d<T> scale;

			scale(0, 0) = v.x;

			scale(1, 1) = v.y;

			scale(2, 2) = v.z;

			scale(3, 3) = static_cast<T>(1);

			return scale;
		}
	};

	//*********************** TRANSFORM 3D *****************************************




	//*********************** TRANSFORM 2D *****************************************
	export
	struct Transform2d
	{
		//Positive theta values rotate counter clockwise.
		template <Number T>
		[[nodiscard]]
		static constexpr auto Rotate(const T theta) noexcept -> Mat2d<T>
		{
			Mat2d<T> rotation;

			const T c = std::cos(theta);
			const T s = std::sin(theta);

			rotation(0, 0) = c;
			rotation(0, 1) = -s;

			rotation(1, 0) = s;
			rotation(1, 1) = c;

			return rotation;
		}


		template <Number T>
		[[nodiscard]]
		static constexpr auto Scale(const T c) -> Mat2d<T>
		{
			Mat2d<T> scale{ c };
			return scale;
		}


		template <Number T>
		[[nodiscard]]
		static constexpr auto Scale(const Vec2d<T>& v) noexcept -> Mat2d<T>
		{
			Mat2d<T> scale;

			scale(0, 0) = v.x;
			scale(1, 1) = v.y;

			return scale;
		}


		template <Number T>
		[[nodiscard]]
		static constexpr auto RotateCounterClock90(const Vec2d<T>& v) noexcept -> Vec2d<T>
		{
			return Vec2d<T>{-v.y, v.x};
		}

		template <Number T>
		[[nodiscard]]
		static constexpr auto RotateClock90(const Vec2d<T>& v) noexcept -> Vec2d<T>
		{
			return Vec2d<T>{v.y, -v.x};
		}

	};

	//*********************** TRANSFORM 2D *****************************************




	//*************************** ANGLES ********************************************
	export
	struct Angles
	{
		template <Number T>
		[[nodiscard]]
		static constexpr auto ToRad(const T a) -> T
		{
			return static_cast<T>(a * std::numbers::pi / 180.0);
		}

		template <Number T>
			requires std::is_arithmetic_v<T>
		[[nodiscard]]
		static constexpr auto ToDeg(const T a) -> T
		{
			return static_cast<T>(a * 180.0 / std::numbers::pi);
		}
	};

	//*************************** ANGLES ********************************************


} //namespace gargantua::math