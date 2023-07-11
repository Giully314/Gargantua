/*
* gargantua/ecs/component_group.ixx
*  
* PURPOSE: Group components.
* 
* CLASSES:
*	ComponentGroup: group all the entites with a specific set of components.
*	MinComponentStorage: utility class used to select the pool with the minimum size.	
* 
* DESCRIPTION:
*	A group allows to group entities with specific components and act on them.
*	We can apply a function using ForEach(f) or just iterate the entities ids with View().
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
*	// NOTE: do not modify the underlyign storage in the loop!
*	auto view = group.View();
*	for (entity_t e : view)
*	{
*		auto& p1 = ecs.Get<Position>(e);
* 
*		...
*	}
*
*/

export module gargantua.ecs.component_group;

import <concepts>;
import <tuple>;
import <limits>;
import <ranges>;
import <algorithm>;
import <utility>;

import gargantua.types;
import gargantua.ecs.entity;
import gargantua.ecs.component_storage;
import gargantua.ds.sparse_set;
import gargantua.mpl.tuple;
import gargantua.generator.coroutine_generator;

namespace gargantua::ecs
{
	/*
	* This struct is used to select the pool of components with the minimum size and 
	* save the iterators. This is done to reduce the number of iterations based 
	* on the property that the intersection of the sets of the components has the 
	* size of the minimum of those sets.
	*/
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

	// TODO: add requirements on the types.
	export
	template <typename ...TComponents>
	class ComponentGroup
	{
	public:
		ComponentGroup(TComponents& ...components_) : components(&components_...)
		{

		}


		// TODO: Add requirements on F at compile time. F must be invocable with 
		// the types passed in the Group.
		/*
		* Apply the function F to every entity that has the set of components 
		* specified at the creation of the group.
		*/
		template <typename F>
			//requires std::invocable<F
		auto ForEach(F&& f) -> void
		{
			auto m = GetMinComponentStorage();

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

		/*
		* Return a generator (coroutine based) that lazily compute the next entity.
		*/
		auto View() -> generator::Generator<entity_t>
		{
			auto m = GetMinComponentStorage();

			for (auto e : std::ranges::subrange(m.b, m.e))
			{
				if (std::apply([e](const auto&... tuple_args)
					{
						return (tuple_args->Has(e) && ...);
					}, components))
				{
					co_yield e;
				}
			}
			co_return;
		}

	private:
		// Return the component storage with less entities.
		auto GetMinComponentStorage() -> MinComponentStorage
		{
			MinComponentStorage m;
			m = mpl::ForEach(components, m);
			return m;
		}

	private:
		using ComponentTuple = std::tuple<non_owned_res<TComponents>...>;
		ComponentTuple components;
	};
} // namespace gargantua::ecs
