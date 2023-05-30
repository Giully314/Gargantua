/*
* gargantua/ecs/component_group.ixx
*  
* PURPOSE: Act on group of components.
* 
* CLASSES:
*	ComponentGroup: group a set of components.
* 
* DESCRIPTION:
* 
* TODO:
*	- iterator.
*	- refactor.
* 
* USAGE:
*	ComponentManager mng;
*	mng.Register<Position>();
*	mng.Register<Velocity>();
*	mng.Register<Acceleration>();
* 
*	auto group = mng.Group<Position, Velocity>();
*	group.ForEach([](Position& p, Velocity& v)
*	{	
*		p += v * 0.1;
*	});
*
*/

export module gargantua.ecs.component_group;

import <concepts>;
import <tuple>;
import <limits>;
import <algorithm>;
import <utility>;

import gargantua.types;
import gargantua.ecs.entity;
import gargantua.ecs.component_storage;
import gargantua.ds.sparse_set;
import gargantua.mpl.tuple;

namespace gargantua::ecs
{
	struct MinComponentStorage
	{
		template <typename T>
		auto operator()(non_owned_res<ComponentStorage<T>> c) -> void
		{
			if (c->Size() < current_min)
			{
				current_min = c->Size();
				b = c->begin();
				e = c->end();
			}
		}

		ds::SparseSet<entity_t>::iterator b;
		ds::SparseSet<entity_t>::iterator e;
		u32 current_min = std::numeric_limits<u32>::max();
	};

	export
	template <typename ...TComponents>
	class ComponentGroup
	{
	public:
		ComponentGroup(TComponents& ...components_) : components(&components_...)
		{

		}


		template <typename F>
			//requires std::invocable<F
		auto ForEach(F&& f) -> void
		{
			MinComponentStorage m;

			m = mpl::ForEach(components, m);

			std::for_each(m.b, m.e, [&](entity_t e)
				{
					if (std::apply([e](const auto&... tuple_args)
						{
							return (tuple_args->Has(e) && ...);
						}, components))
					{
						std::apply([&](auto&... tuple_args)
							{
								f((*tuple_args)[e]...);
							}, components);
					}
				});
		}


	private:
		using ComponentTuple = std::tuple<non_owned_res<TComponents>...>;
		ComponentTuple components;
	};
} // namespace gargantua::ecs
