///*
//
//
//TODO: 
//	How to map the same components in different orders to an archetype? Use some ordering? Or a check if the components 
//	are already registered in an archetype? All of these is done at compile time.
//*/
//
//export module gargantua.ecs.ecs:archetype_manager;
//
//import <unordered_map>;
//import <typeinfo>;
//import <typeindex>;
//import <concepts>;
//
//
//import :archetype;
//import :entity;
//
//import gargantua.types;
//import gargantua.mpl.type_list;
//
//
//
//export namespace gargantua::ecs
//{
//	class ArchetypeManager
//	{
//	public:
//		
//		/*
//		* Register an archetype with the components specified.
//		* Note that calling this function with the same components but in different orders produce different 
//		* archetypes for now.
//		* Complexity: O(sizeof(TComponents)).
//		*/
//		template <std::semiregular ...TComponents>
//		auto RegisterArchetype() -> void
//		{
//			//TODO: sort the components and check if they are already registered
//			auto idx = GetTypeIndex<TComponents...>;
//			if (!archetypes.contains(idx))
//			{
//				archetypes[idx] = CreateUniqueRes<Archetype<TComponents...>>();
//			}
//		}
//
//
//		/*
//		* Unregister the archetypes with the components passed.
//		* Complexity: O(sizeof(TComponents) * number of components to destroy).
//		*/
//		template <std::semiregular ...TComponents>
//		auto UnregisterArchetype() -> void
//		{
//			auto idx = GetTypeIndex<TComponents...>;
//			if (auto it = archetypes.find(idx); it != archetypes.end())
//			{
//				archetypes.erase(it);
//			}
//		}
//
//
//		/*
//		* Get the archetype associated to the components passed.
//		* Note that if the archetype is not registered an exception is thrown.
//		*/
//		template <std::semiregular ...TComponents>
//		[[nodiscard]]
//		auto GetArchetype() -> Archetype<TComponents...>&
//		{
//			auto idx = GetTypeIndex<TComponents...>;
//			return archetypes.at(idx);
//		}
//
//	private:
//		std::unordered_map<std::type_index, UniqueRes<ArchetypeHandler>> archetypes;
//
//
//		template <std::semiregular ...TComponents>
//		[[nodiscard]]
//		auto GetTypeIndex() const noexcept -> std::type_index
//		{
//			using components = mpl::TypeList<TComponents...>;
//			return std::type_index{ typeid(components) };
//		}
//	};
//} //namespace gargantua::ecs