#pragma once

#include "Gargantua/ECS/ComponentManager.hpp"

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


		class ComponentManagerTest
		{
		public:
			void Run()
			{
				ECS::ComponentManager<PositionComponent> mng;

				for (natural_t i = 0; i < 100; ++i)
				{
					mng.Register(i, i + 10.5f, i * 2 * 100.3f);
				}

				for (natural_t i = 0; i < 100; ++i)
				{
					auto& p = mng.Get(i);
					GRG_CORE_INFO("Entity {}, position: ( {} , {} )", i, p.x, p.y);
				}

				for (natural_t i = 0; i < 100; ++i)
				{
					mng.Unregister(i);
				}
			}
		};

	} //namespace Test
} //namespace Gargantua