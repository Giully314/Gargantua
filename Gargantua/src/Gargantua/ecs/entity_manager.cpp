/*
gargantua/ecs/entity_manager.cpp
*/

module gargantua.ecs.ecs:entity_manager;


namespace gargantua::ecs
{
	auto EntityManager::CreateEntity() -> entity_t
	{
		//If no entity is available, create a new one.
		if (available == 0)
		{
			entity_t e = EntityManipulation::MakeEntity(g.Get(), 0);
			entities.push_back(e);
			return e;
		}

		//Get a recycled entity.
		--available;
		auto temp_next = next;
		next = EntityManipulation::ExtractID(entities[next]);
		entities[temp_next] = EntityManipulation::InsertIdInEntity(entities[temp_next], temp_next);

		return entities[temp_next];
	}


	auto EntityManager::DestroyEntity(entity_t e) -> void
	{
		auto id = EntityManipulation::ExtractID(e);
		//increment the generation number 
		++entities[id];
		++available;
		
		//if this is the first entity to be recyled the procedure is a little bit different
		if (available == 1)
		{
			next = id;
		}
		else
		{
			entities[id] = EntityManipulation::InsertIdInEntity(entities[id], next);
			next = id;
		}
	}
} //namespace gargantua::ecs