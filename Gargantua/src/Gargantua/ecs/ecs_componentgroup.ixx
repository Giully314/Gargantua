/*
* gargantua/ecs/ecs_componentgroup.ixx
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
*	It can be seen as a view: it doesn't own the memory but it can act on the components.
*	
*	One problem right now is the fact that we check if the entity has all the components;
*	this problem will be solved with the introduction of sorting the entities.
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
*	group.ForEach([](Position& p, const Velocity& v)
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
import gargantua.mpl.typelist;
import gargantua.mpl.tuple;
import gargantua.gen.coroutine_generator;

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
		constexpr explicit MinComponentStorage() = default;

		template <typename T>
		constexpr auto operator()(non_owned_res<ComponentStorage<T>> c) -> void
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

	template <typename T> 
	struct ExtractValueType
	{
		using Type = typename T::value_type;
	};


	// TODO: add requirements on the types.
	export template <typename ...TComponents>
	class ComponentGroup
	{
	public:
		constexpr explicit ComponentGroup(TComponents& ...components_) : components(&components_...)
		{

		}


		
		/*
		* Apply the function F to every entity that has the set of components 
		* specified at the creation of the group.
		*/
		template <typename F>
		// TODO: this requires must be refactored because it's ugly and it works directly with typelists.
		// This requires check if the arguments of the function passed (cv ref are removed) are the same 
		// (in order) as the types of the group.
			/*requires mpl::AreEqualV<mpl::RemoveCVRefT<mpl::ParamsOfFunctionT<F>>, 
						mpl::TransformT<mpl::TypeList<TComponents...>, ExtractValueType>>*/
		constexpr auto ForEach(F&& f) -> void
		{
			auto m = GetMinComponentStorage();

			std::for_each(m.b, m.e, [&](const entity_t e)
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
		auto View() -> gen::Generator<entity_t>
		{
			auto m = GetMinComponentStorage();

			// NOTE: e can't be const because the return value of the coroutine is a reference (?).
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
		constexpr auto GetMinComponentStorage() -> MinComponentStorage
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
