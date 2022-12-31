///*
//
//*/
//
//export module gargantua.ecs.ecs:archetype;
//
//import <concepts>;
//import <typeinfo>;
//import <typeindex>;
//import <unordered_map>;
//import <vector>;
//import <utility>;
//
//import gargantua.datastructures.sparse_set;
//
//import :entity;
//
//
//export namespace gargantua::ecs
//{
//	class ArchetypeHandler
//	{
//	public:
//		virtual ~ArchetypeHandler() = default;
//	};
//
//
//
//	
//	class Archetype
//	{
//	public:
//		template <typename T>
//		using Container = std::vector<T>;
//
//
//		template <std::semiregular ...TComponents>
//		Archetype()
//
//		auto Emplace(const entity_t e) -> void
//		{
//			const auto id = ecs::EntityManipulation::ExtractID(e);
//			entities_registered.insert(id);
//			std::apply([](auto&& ...vs) { (vs.emplace_back(), ...); }, components);
//		}
//
//
//		auto Erase(const entity_t e) -> void
//		{
//			using std::swap;
//			auto id = ecs::EntityManipulation::ExtractID(e);
//			auto idx = entities_registered.index_of(id);
//			entities_registered.erase(e);
//			std::apply([=](auto&& ...vs) 
//				{ 
//					(swap(vs[idx], vs.back()), ...);
//					(vs.pop_back(), ...);
//				}, components);
//		}
//
//
//		/*
//		* Extract the set of components from this archetype.
//		*/
//		auto Extract(const entity_t e) -> std::tuple<TComponents...> 
//		{
//			const auto id = ecs::EntityManipulation::ExtractID(e);
//			const auto idx = entities_registered.index_of(id);
//
//		}
//
//
//		template <std::semiregular TComponent>
//			requires (std::same_as<TComponents, TComponent> || ...)
//		[[nodiscard]]
//		auto Get(entity_t e) -> TComponent&
//		{
//			auto id = ecs::EntityManipulation::ExtractID(e);
//			auto idx = entities_registered.index_of(id);
//			return std::get<Container<TComponent>>(components)[idx];
//		}
//		
//		
//		template <std::semiregular TComponent>
//			requires (std::same_as<TComponents, TComponent> || ...)
//		[[nodiscard]]
//		auto GetComponentArray() -> const Container<TComponent>&
//		{
//			return std::get<Container<TComponent>>(components);
//		}
//
//
//	private:
//		datastructures::SparseSet<entity_t> entities_registered;
//		const std::unordered_map<std::type_index,  components;
//	};
//} //namespace gargantua::ecs
