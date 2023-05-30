export module gargantua.test.ecs.components;

import gargantua.math.vec2d;

export namespace gargantua::test
{
	struct Position
	{
		Position() = default;

		Position(float x, float y) : p(x, y) { }

		Position(const math::Vec2df& p_) : p(p_) { }

		math::Vec2df p;
	};

	struct Velocity
	{
		Velocity() = default;

		Velocity(float x, float y) : v(x, y) { }

		Velocity(const math::Vec2df& v_) : v(v_) { }

		math::Vec2df v;
	};

	struct Acceleration
	{
		Acceleration() = default;

		Acceleration(float x, float y) : a(x, y) { }

		Acceleration(const math::Vec2df& a_) : a(a_) { }

		math::Vec2df a;
	};
}