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
		static auto Dot(const Vec2d<T>& v1, const Vec2d<T>& v2) -> T
		{
			return v1.Dot(v2);
		}


		template <Number T>
		static auto Hadamard(const Vec2d<T>& v1, const Vec2d<T>& v2) -> Vec2d<T>
		{
			return { v1.x * v2.x, v1.y * v2.y };
		}


		template <Number T>
		static auto Cross(const Vec2d<T>& v1, const Vec2d<T>& v2) -> T
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
		static Mat4d<T> Orthographic(const T l, const T b, const T r, const T t, const T n, const T f)
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
		static Mat4d<T> Orthographic(const T l, const T b, const T r, const T t)
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
		static Mat4d<T> Translate(const Vec3d<T>& v)
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
		static Mat4d<T> RotateZ(const T a)
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
		static Mat4d<T> Scale(const T c)
		{
			Mat4d<T> scale{ c };

			scale(3, 3) = static_cast<T>(1);

			return scale;
		}

		template <Number T>
		static Mat4d<T> Scale(const Vec3d<T>& v)
		{
			Mat4d<T> scale;

			scale(0, 0) = v[0];

			scale(1, 1) = v[1];

			scale(2, 2) = v[2];

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
		static Mat2d<T> Rotate(const T theta)
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
		static Mat2d<T> Scale(const T c)
		{
			Mat2d<T> scale{ c };

			return scale;
		}


		template <Number T>
		static Mat2d<T> Scale(const Vec2d<T>& v)
		{
			Mat2d<T> scale;

			scale(0, 0) = v[0];

			scale(1, 1) = v[1];

			return scale;
		}


		template <Number T>
		static Vec2d<T> RotateCounterClock90(const Vec2d<T>& v)
		{
			return Vec2d<T>{-v.y, v.x};
		}

		template <Number T>
		static Vec2d<T> RotateClock90(const Vec2d<T>& v)
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
		static T ToRad(const T a)
		{
			return static_cast<T>(a * std::numbers::pi / 180.0);
		}

		template <Number T>
			requires std::is_arithmetic_v<T>
		static T ToDeg(const T a)
		{
			return static_cast<T>(a * 180.0 / std::numbers::pi);
		}
	};

	//*************************** ANGLES ********************************************


} //namespace gargantua::math