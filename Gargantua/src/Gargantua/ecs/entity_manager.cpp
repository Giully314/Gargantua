/*
gargantua/ecs/entity_manager.cpp
*/

module gargantua.ecs.entity_manager;


namespace gargantua::ecs
{
	auto EntityManager::CreateEntity() -> entity_t
	{
		//If no entity is available, create a new one.
		if (available == 0)
		{
			entity_t e = CreateEntityID();
			entities.push_back(e);
			return e;
		}

		//Get a recycled entity.
		auto temp_next = next;
		next = ExtractEntity(entities[next]);
		entities[temp_next] = InsertEntity(temp_next, entities[temp_next]);

		return entities[temp_next];
	}


	auto EntityManager::DestroyEntity(entity_t e_id) -> void
	{
		auto e = ExtractEntity(e_id);
		//increment the generation number 
		++entities[e];
		++available;
		
		//if this is the first entity to be recyled the procedure is a little bit different
		if (available == 1)
		{
			next = e;
		}
		else
		{
			entities[e] = InsertEntity(next, entities[e]);
			next = e;
		}
	}
} //namespace gargantua::ecs