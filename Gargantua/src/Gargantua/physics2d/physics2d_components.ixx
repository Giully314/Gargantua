/*
* gargantua/physics2d/physics2d_components.ixx
* 
* PURPSOSE: Define physical properties of an entity with components.
*	
* CLASSES:
*	PositionComponent:	position of an entity.
*	VelocityComponent:	velocity of an entity.
*	ForceComponent:		force applied on an entity.
*	MassComponent:		mass and inertia of an entity.
*	
*	RotationComponent:			orientation of an entity.
*	AngularVelocityComponent:	angular velocity of an entity.
*	TorqueComponent:			torque applied to an entity.
* 
*	QuadComponent: size of the quad.
*	
*	RigidBodyComponent:		info about the rigid body (coeff of restituion, frictions).
*	QuadCollisionComponent: info about the collision between two quads.
* 
* 
* 
* TODO:
*	- check if 2 or more components can be packed into a singular component base on how the
*		logic is implemented.
*/

export module gargantua.physics2d.components;

import <vector>;
import <utility>;

import gargantua.types;
import gargantua.math.vec2d;
import gargantua.math.math_functions;
import gargantua.ecs.entity;

export namespace gargantua::physics2d
{
	// Not used for now.
	enum class BodyType : u8
	{
		Static,		// The body is still, no impulse.
		Dynamic,	// The body can be moved when interacts with other bodies in the impulse resolution.
		Kinematics, // The body can be moved but doesn't interact with other bodies in the impulse resolution.
	};


	struct PositionComponent
	{
		PositionComponent() = default;
		PositionComponent(const math::Vec2df& position) : p(position)
		{

		}

		// Entity position in the world coordinate system.
		math::Vec2df p;
	};


	struct VelocityComponent
	{
		VelocityComponent() = default;
		VelocityComponent(const math::Vec2df& velocity) : v(velocity)
		{

		}

		math::Vec2df v;
	};

	struct AccelerationComponent
	{
		AccelerationComponent() = default;
		AccelerationComponent(const math::Vec2df& acceleration) : a(acceleration)
		{

		}

		math::Vec2df a;
	};

	struct ForceComponent
	{
		ForceComponent() = default;
		ForceComponent(const math::Vec2df& force) : f(force)
		{

		}

		// Force applied to the entity.
		math::Vec2df f;
	};


	// Precondition: m >= 0.
	struct MassComponent
	{
		MassComponent() = default;
		
		MassComponent(const f32 m_)
		{
			if (m_ == 0.0f)
			{
				inv_m = 0.0f;
				m = 0.0f;
			}
			else
			{
				m = m_;
				inv_m = 1.0f / m;
			}
		}

		auto SetMass(const f32 new_mass) -> void
		{
			if (new_mass == 0.0f)
			{
				SetInfinite();
				return;
			}
			m = new_mass;
			inv_m = 1.0f / new_mass;
		}

		auto SetInfinite() -> void
		{
			inv_m = 0.0f;
			m = 0.0f;
		}

		// Mass is in kg.
		f32 m = 1.0f;
		f32 inv_m = 1.0f;
	};


	struct MomentInertiaComponent
	{
		MomentInertiaComponent() = default;

		MomentInertiaComponent(const f32 i_)
		{
			if (i_ == 0.0f)
			{
				inv_i = 0.0f;
				i = 0.0f;
			}
			else
			{
				i = i_;
				inv_i = 1.0f / i;
			}
		}


		auto SetInfinite() -> void
		{
			i = 0.0f;
			inv_i = 0.0f;
		}


		auto SetInertia(const f32 i) -> void
		{
			if (i == 0.0f)
			{
				SetInfinite();
				return;
			}

			this->i = i;
			inv_i = 1.0f / i;
		}
		
		// z axis
		f32 i = 1.0f; 
		f32 inv_i = 1.0f;
	};


	struct RotationComponent
	{
		RotationComponent() = default;

		RotationComponent(const f32 theta_) : theta(theta_)
		{

		}

		//constexpr
		auto FromDegree(const f32 d) -> void
		{
			theta = math::Angles::ToRad(d);
		}

		// In radians
		f32 theta = 0.0f;
	};
	

	struct AngularVelocityComponent
	{
		AngularVelocityComponent() = default;

		AngularVelocityComponent(const f32 omega_) : omega(omega_)
		{

		}

		f32 omega = 0.0f;
	};


	struct TorqueComponent
	{
		TorqueComponent() = default;

		TorqueComponent(const f32 t_) : t(t_)
		{

		}

		f32 t = 0.0f;
	};


	struct QuadComponent
	{
		QuadComponent() = default;

		QuadComponent(f32 half_width, f32 half_height) : r(half_width, half_height)
		{

		}

		QuadComponent(const math::Vec2df& half_size_) : r(half_size_)
		{

		}

		// For now it is assumed that the shape is positioned at the origin in the object
		// coordinate system.
		// radius of the quad shape. 
		math::Vec2df r{1.0f, 1.0f};
	};


	struct RigidBodyComponent
	{
		RigidBodyComponent() = default;

		RigidBodyComponent(f32 static_friction_, f32 dynamic_friction_, f32 restituition_) :
			static_friction(static_friction_),
			dynamic_friction(dynamic_friction_),
			restituition(restituition_)
		{

		}

		// Usually dynamic_friction < static_friction. We can force this constraint using a setter,
		// but i think it's better to let the free choice.
		f32 static_friction = 0.5f;
		f32 dynamic_friction = 0.1f;
		f32 restituition = 1.0f;
	};


	struct CollisionInfoComponent
	{
		CollisionInfoComponent() = default;


		CollisionInfoComponent(const math::Vec2df normal_, f32 penetration_) : normal(normal_),
			penetration(penetration_)
		{

		}

		CollisionInfoComponent(const std::pair<math::Vec2df, f32>& info) :
			CollisionInfoComponent(info.first, info.second)
		{

		}


		math::Vec2df normal;
		f32 penetration = 0.0f;
	};

	struct QuadCollisionComponent
	{
		QuadCollisionComponent() = default;

		QuadCollisionComponent(std::vector<ecs::entity_t>&& ents) : entities_in_collision(ents)
		{

		}

		//TODO: for better cache maybe use one vector of pair <entity_t, CollisionInfo>? 
		// These 2 vectors are aligned: info[0] are the info about collision with the entities_in_collision[0]
		std::vector<ecs::entity_t> entities_in_collision;
		std::vector<CollisionInfoComponent> collisions_info;
	};
} // namespace gargantua::physics