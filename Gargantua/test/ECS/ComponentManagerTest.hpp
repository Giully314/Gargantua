#pragma once

#include "Gargantua/MPL/TypeList.hpp"

#include "Gargantua/ECS/ComponentManager.hpp"
#include "Gargantua/ECS/ComponentStorage.hpp"

#include "Gargantua/Core/EngineLogger.hpp"

namespace Gargantua
{
	namespace Test
	{
		struct PositionComponent
		{
			PositionComponent() = default;

			PositionComponent(float x_, float y_) : x(x_), y(y_)
			{

			}

			float x = 0.0f;
			float y = 0.0f;
		};

		struct VelocityComponent
		{
			VelocityComponent() = default;

			VelocityComponent(float x_, float y_) : x(x_), y(y_)
			{

			}

			float x = 0.0f;
			float y = 0.0f;
		};

		struct AccelerationComponent
		{
			AccelerationComponent() = default;

			AccelerationComponent(float x_, float y_) : x(x_), y(y_)
			{

			}

			float x = 0.0f;
			float y = 0.0f;
		};


		class ComponentManagerTest
		{
		public:
			void Run()
			{
				using ComponentsList = MPL::TypeList<PositionComponent, VelocityComponent, AccelerationComponent>;

				ECS::ComponentManager<ComponentsList> mng;

				mng.Register<PositionComponent>(0, 13.1f, 12.3f);
				mng.Register<PositionComponent>(1, 233.1f, 112.432f);
				
				auto& p1 = mng.Get<PositionComponent>(0);
				auto& p2 = mng.Get<PositionComponent>(1);

				GRG_CORE_INFO("{} {}", p1.x, p1.y);
				GRG_CORE_INFO("{} {}", p2.x, p2.y);
			}
		};

	} //namespace Test
} //namespace Gargantua