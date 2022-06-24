#pragma once
/*
Sandbox/src/Stages.hpp


PURPOSE:

CLASSES:

DESCRIPTION:


*/

#include <Gargantua/Types.hpp>

#include <Gargantua/Core/Stage.hpp>
#include <Gargantua/Core/EngineSystems.hpp>

#include <Gargantua/Input/KeyCodes.hpp>

#include <Gargantua/Time/TimeStep.hpp>

#include <Gargantua/ECS/Types.hpp>

#include <Gargantua/Systems/ECSSystem.hpp>


#include <Gargantua/Renderer/Utility.hpp>
#include <Gargantua/Renderer/OrthoCamera.hpp>
#include <Gargantua/Renderer/OrthoCameraController.hpp>

#include <Gargantua/Math/Vec2d.hpp>
#include <Gargantua/Math/Vec4d.hpp>

#include <utility>


namespace Sandbox
{
	using namespace Gargantua;



	struct Quad
	{
		Math::Vec2df position;
		Math::Vec2df scale{1, 1};

		real_t rotation = 0.0f;

		Math::Vec4df color{ 1, 1, 1, 1 };

		SharedRes<Renderer::Texture2d> texture;
	};


	class RenderTestStage : public Gargantua::Core::Stage
	{
	public:
		RenderTestStage(Core::EngineSystems systems_) : systems(std::move(systems_))
		{

		}

		
		void Start() override;

		void End() override { }


		void Execute(const Time::TimeStep& ts) override;

		void RenderGUI() override;

	private:
		Core::EngineSystems systems;

		UniqueRes<Renderer::OrthoCamera> ortho_cam;
		Renderer::OrthoCameraController controller;
		
		Quad player;
		Quad player2;
		Quad background;
	};
} //namespace Sandbox



//
//template <typename T, typename U>
//void QuadConvexShape(ECS::Entity e, real_t length, SharedRes<Systems::ECSSystem<T, U>>& ecs)
//{
//	Physics::ConvexShapeComponent& shape = ecs->Get<Physics::ConvexShapeComponent>(e);
//
//	Physics::RigidBodyFunctions::SquareShape(shape, length);
//}
//
////Register all the necessary components for the systems and register the entity into the systems.
//template <typename T, typename U>
//void RegisterEntityToPhysicsSystems(ECS::Entity e, SharedRes<Systems::ECSSystem<T, U>>& ecs)
//{
//	auto& t = ecs->Register<Physics::TransformComponent>(e);
//
//	Physics::BodyComponent& b = ecs->Register<Physics::BodyComponent>(e);
//	b.radius = 1;
//	ecs->Register<Physics::ConvexShapeComponent>(e);
//	ecs->Register<Physics::MoveComponent>(e);
//	ecs->Register<Physics::MassComponent>(e, 1.0f);
//	ecs->Register<Physics::ThrustComponent>(e);
//	ecs->Register<Physics::ForceComponent>(e);
//
//	const real_t length = 0.1f;
//	Physics::ConvexShapeComponent& shape = ecs->Get<Physics::ConvexShapeComponent>(e);
//
//	Physics::RigidBodyFunctions::SquareShape(shape, length);
//
//	b.position = shape.centroid;
//	t.position = shape.points[1]; //left upper corner of the square
//
//
//	ecs->Register<Physics::NewtonianECSSystem>(e);
//	ecs->Register<Physics::CollisionTestECSSystem>(e);
//}
//
//
//template <typename T, typename U>
//void RegisterEntityToRendererSystem(ECS::Entity e, std::string sprite_name,
//	SharedRes<Systems::ECSSystem<T, U>>& ecs)
//{
//	ecs->Register<Renderer::SpriteComponent>(e, Renderer::Utility::CreateTX2d(sprite_name));
//	ecs->Register<Renderer::RendererECSSystem>(e);
//}
//
//
//template <typename T, typename U>
//void RegisterEntityToInputSystem(ECS::Entity e, SharedRes<Systems::ECSSystem<T, U>>& ecs)
//{
//	Physics::InputThrustComponent& input = ecs->Register<Physics::InputThrustComponent>(e);
//
//	real_t thrust = 1000.f;
//
//	input.right_thrust.first = Input::Key::D;
//	input.right_thrust.second = Math::Vec2df{ thrust, 0.0f };
//
//	input.left_thrust.first = Input::Key::A;
//	input.left_thrust.second = Math::Vec2df{ -thrust, 0.0f };
//
//	input.up_thrust.first = Input::Key::W;
//	input.up_thrust.second = Math::Vec2df{ 0.0f, thrust };
//
//	input.down_thrust.first = Input::Key::S;
//	input.down_thrust.second = Math::Vec2df{ 0.0f, -thrust };
//
//	input.left_rotation.first = Input::Key::LEFT;
//	input.right_rotation.first = Input::Key::RIGHT;
//
//	ecs->Register<Physics::InputThrustECSSystem>(e);
//}