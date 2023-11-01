/*
* gargantua/level/map_grid.ixx
* 
* PURPOSE: 2d grid.
* 
* CLASSES:
*	MapGrid: a 2d grid used as a base abstraction for world building.
* 
* DESCRIPTION:
* 
* TODO:
*	- is possible to treat this class as an entity in the ecs?
*/

export module gargantua.level.tilemap;

import <vector>;
import <memory>;
import <format>;

import gargantua.types;
import gargantua.math.vec2d;
import gargantua.ds.grid;
import gargantua.level.tileblock;
import gargantua.render;
import gargantua.ecs;
import gargantua.physics2d;

// Note that this create a circular dependency on a module level. What I mean is that level is used by the 
// scene module and using one of the scene component create a circular dependency. This can be solved by moving
// all the ecs components into a separate module.
import gargantua.scene.scene_components; 


export namespace gargantua::level
{
	class TileMap
	{
	public:
		explicit constexpr TileMap() : TileMap(30, 30, 16) { }

		// Precondition: parameters must be greater than 0.
		explicit constexpr TileMap(u32 width, u32 height, u32 block_size_,
			non_owned_res<ecs::ECSSystem> ecs_s) : map(width, height, ecs::null_entity),
			block_size(block_size_), ecs_system(ecs_s)
		{

		}


		// Precondition: parameters must be greater than 0.
		explicit constexpr TileMap(u32 width, u32 height, u32 block_size) : 
			TileMap(width, height, block_size, nullptr)
		{

		}


		constexpr auto SetECS(non_owned_res<ecs::ECSSystem> ecs_s) -> void
		{
			ecs_system = ecs_s;
		}


		// Given a position in the world, get the (x, y) in the grid associated to that position.
		constexpr auto GetBlockAtPoint(const math::Vec2df& point) const -> math::Vec2du
		{
			auto half_block_size = block_size / 2.0f;
			return {
				static_cast<u32>((point.x - position.x + half_block_size) / static_cast<float>(block_size)),
				static_cast<u32>((point.y - position.y + half_block_size) / static_cast<float>(block_size))
			};
		}

		// Set the grid block associated to that position in the map and create/update the ecs entity associated.
		constexpr auto SetBlockAtPoint(const math::Vec2du& idx) -> void
		{
			using namespace physics2d;
			using namespace render;

			if (auto e = map(idx.x, idx.y); e == ecs::null_entity)
			{
				// Create the entity
				e = ecs_system->Create();
				map(idx.x, idx.y) = e;

				PhysicsSystem::Instance().Register(e, 0.0f, { 1.0f, 1.0f }, *ecs_system);
				auto& p = ecs_system->Get<PositionComponent>(e);
				p.p = position + static_cast<math::Vec2df>(idx);

				RendererSystem::Instance().Register(e, *ecs_system);
				auto& t = ecs_system->Get<TransformComponent>(e);
				t.position = { p.p, 0.0f };
				auto& r = ecs_system->Get<TextureComponent>(e);
				r.color = { 1.0f, 0.0f, 0.0f, 1.0f };

				auto& s = ecs_system->Emplace<scene::TagComponent>(e, std::format("Block {} {}", idx.x, idx.y));
			}
			else
			{
				// Update the entity
			}
		}


		//// Given a position in the world, set the player (x, y) associated to that position.
		//constexpr auto SetPlayerAtPoint(const math::Vec2df& point, ecs::entity_t player) -> math::Vec2du
		//{
		//	auto pos = GetBlockAtPoint(point);
		//}



		/*constexpr auto Block(const math::Vec2du& idx) -> TileBlock&
		{
			return map(idx.x, idx.y);
		}

		constexpr auto Block(const math::Vec2du& idx) const -> const TileBlock&
		{
			return map(idx.x, idx.y);
		}

		constexpr auto Block(const u32 x, const u32 y) -> TileBlock&
		{
			return map(x, y);
		}

		constexpr auto Block(const u32 x, const u32 y) const -> const TileBlock&
		{
			return map(x, y);
		}*/


		constexpr auto Block(const u32 x, const u32 y) const -> ecs::entity_t
		{
			return map(x, y);
		}


		auto Position() -> math::Vec2df&
		{
			return position;
		}

		auto Position() const -> const math::Vec2df&
		{
			return position;
		}
		
	private:
		auto RegisterBlockToECS(ecs::entity_t e) -> void;

		auto UpdateBlockECS(ecs::entity_t e) -> void;
		

	private:
		ds::Grid<ecs::entity_t> map;
		u32 block_size;
		math::Vec2df position;
		non_owned_res<ecs::ECSSystem> ecs_system;
		// TODO: additional texture to render as background
	};
} // namespace gargantua::level