/*
* gargantua/ecs/entity_manager.cpp
* 
* DESCRIPTION: 
*	Check this for more info about the methods used to create/destroy entities:
*	https://skypjack.github.io/2019-05-06-ecs-baf-part-3/
*/


module gargantua.ecs.entity_manager;

namespace gargantua::ecs
{
	auto EntityManager::Create() -> entity_t
	{
		//If no entity is available, create a new one.
		if (available == 0)
		{
			entity_t id = EntityManipulation::MakeID(0, g.Next());
			entities.push_back(id);
			return id;
		}

		//Get a recycled entity.
		--available;
		auto temp_next = next;
		next = EntityManipulation::Entity(entities[next]);
		entities[temp_next] = EntityManipulation::InsertEntityInID(entities[temp_next], temp_next);

		return entities[temp_next];
	}


	auto EntityManager::Destroy(const entity_t id) -> void
	{
		auto entity = EntityManipulation::Entity(id);
		//increment the generation number 
		auto new_gen = EntityManipulation::Generation(entities[entity]) + 1;
		entities[entity] = EntityManipulation::InsertGenerationInID(entities[entity], new_gen);
		++available;

		//if this is the first entity to be recyled the procedure is a little bit different
		if (available == 1)
		{
			next = entity;
		}
		else
		{
			entities[entity] = EntityManipulation::InsertEntityInID(entities[entity], next);
			next = entity;
		}
	}
} //namespace gargantua::ecs