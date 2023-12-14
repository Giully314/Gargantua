///*
//* gargantua/cell/cell_particleworld.ixx
//* 
//* PURPOSE:
//* 
//* CLASSES:
//* 
//* DESCRIPTION:
//* 
//* TODO:
//*	- create an intermediary cache for particle entities. We can't create/destroy particles in the ecs system
//*	at high rate due to performance reasons so we can cache particles for reuse.
//*/
//
//export module gargantua.cell.particleworld;
//
//import <variant>;
//import <concepts>;
//
//import gargantua.types;
//import gargantua.ecs;
//import gargantua.time.time_step;
//import gargantua.ds.grid;
//import gargantua.cell.particle;
//import gargantua.cell.particles;
//
//namespace gargantua::cell
//{
//	export class ParticleWorld
//	{
//	public:
//		explicit ParticleWorld(const u32 width, const u32 height, non_owned_res<ecs::ECSSystem> ecs_system) : 
//			grid{ width, height }, context{ ecs_system }
//		{
//
//		}
//
//
//		auto Run(const time::TimeStep& ts) -> void
//		{
//			// Number of particles, used as trick for switch case optimization.
//			static constexpr auto size = 2; 
//			for (u32 i = 1; i < grid.Height() - 1; ++i)
//			{
//				for (u32 j = 1; j < grid.Width() - 1; ++j)
//				{
//					// TODO: refactor this to create my own implementation of std::visit (apperently is slow).
//					auto& p = grid(i, j);
//					switch (p.index())
//					{
//					case 0: if constexpr (0 < size) (*this)(*std::get_if<0>(&p), i, j); break;
//					case 1: if constexpr (1 < size) (*this)(*std::get_if<1>(&p), i, j); break;
//					default:
//						break;
//					}
//				}
//			}
//		}
//
//	private:
//		auto operator()(const EmptyParticle& p, u32 x, u32 y) -> void
//		{
//
//		}
//
//
//		auto operator()(const SandParticle& p, u32 x, u32 y) -> void
//		{
//			if (auto t = std::get_if<0>(&grid(x, y + 1)); t)
//			{
//				grid(x, y) = EmptyParticle{};
//				grid(x, y + 1) = p;
//			}
//			else if(auto t = std::get_if<0>(&grid(x - 1, y + 1)); t)
//			{
//				grid(x, y) = EmptyParticle{};
//				grid(x - 1, y + 1) = p;
//			}
//			if (auto t = std::get_if<0>(&grid(x + 1, y + 1)); t)
//			{
//				grid(x, y) = EmptyParticle{};
//				grid(x + 1, y + 1) = p;
//			}
//		}
//
//
//	private:
//		using Particles = std::variant<EmptyParticle, SandParticle>;
//
//		ds::Grid<Particles> grid;
//		non_owned_res<ecs::ECSSystem> context;
//	};
//} // namespace gargantua::cell
//
