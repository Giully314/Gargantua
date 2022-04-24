#pragma once

#include "Gargantua/ECS/EntityManager.hpp"
#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/Generators/SequentialNumberGenerator.hpp"
#include "Gargantua/Core/EngineLogger.hpp"

#include "Gargantua/Types.hpp"

#include <vector>

namespace Gargantua
{
	namespace Test
	{
		class EntityManagerTest
		{
		public:
			void Run()
			{
				ECS::EntityManager<Generators::SequentialNumberGenerator> mng;
				std::vector<ECS::Entity> entities;

				for (natural_t i = 0; i < 100; ++i)
				{
					entities.push_back(mng.Create());
				}

				for (auto e : entities)
				{
					GRG_CORE_INFO("Destroying entity {}", e);
					mng.Destroy(e);
				}

				entities.clear();

				for (natural_t i = 0; i < 200; ++i)
				{
					entities.push_back(mng.Create());
				}


				if (mng.InUse(entities.front()))
				{
					GRG_CORE_INFO("Entity {} ALIVE", entities.front());
				}

				for (auto e : entities)
				{
					GRG_CORE_INFO("Destroying entity {}", e);
					mng.Destroy(e);
				}
				
			}
		};

	} //namespace Test
} //namespace Gargantua