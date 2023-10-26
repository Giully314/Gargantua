/*
* gargantua/render/texture2d_system.ixx
* 
* PURPOSE: Manage 2d textures.
*
* CLASSES:
*	Texture2dSystem: Singleton for create/destroy/access 2d textures by name.
* 
* DESCRIPTION:
*	Manage Texture2d objects using shared_ptr. 
* 
* USAGE:	
*	auto& ts = Texture2dSystem::Instance();
*	auto my_texture = ts.GetFromFile("MyTexturePath");
*	
*	// later in another section of the program.
*	auto my_texture = ts.Get("MyTexturePath");
* 
*	
*	// If a texture is not present, create a new one with the name passed.
*	auto white_texture = ts.Get("WhiteTexture");
*/


export module gargantua.render.texture2d_system;

import <unordered_map>;
import <ranges>;
import <string>;
import <string_view>;
import <functional>;

import gargantua.types;
import gargantua.render.texture2d;

namespace gargantua::render
{
	export 
	class Texture2dSystem : private NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static
		auto Instance() -> Texture2dSystem&
		{
			static Texture2dSystem sys;
			return sys;
		}

		/*
		* Load the texture from a file if not present in the cache.
		*/
		[[nodiscard]]
		auto GetFromFile(std::string_view name) -> shared_res<Texture2d>
		{
			if (auto f = textures.find(name); f != textures.end())
			{
				return f->second;
			}

			// Load texture.
			if (auto t = textures.emplace(std::make_pair(name, CreateSharedRes<Texture2d>())); t.second)
			{
				t.first->second->Load(name);
				return t.first->second;
			}
			// TODO: in case of error in the previous if, report.
			return nullptr;
		}

		/*
		* Get a texture with the given name. If not present, create an empty new one.
		*/
		[[nodiscard]]
		auto Get(std::string_view name) -> shared_res<Texture2d>
		{
			if (auto f = textures.find(name); f != textures.end())
			{
				return f->second;
			}

			if (auto t = textures.emplace(std::make_pair(name, CreateSharedRes<Texture2d>())); t.second)
			{
				return t.first->second;
			}
			// TODO: in case of error in the previous if, report.
			return nullptr;
		}


		/*
		* Return a view of the names of all textures registered.
		*/
		auto GetTextureNames()
		{
			return std::views::keys(textures);
		}

	private:
		Texture2dSystem() = default;

	private:
		template <typename ...Bases>
		struct overload : Bases...
		{
			using is_transparent = void;
			using Bases::operator()...;
		};

		struct char_pointer_hash
		{
			auto operator()(const char* ptr) const noexcept
			{
				return std::hash<std::string_view>{}(ptr);
			}
		};

		using string_hash = overload<
			std::hash<std::string>,
			std::hash<std::string_view>,
			char_pointer_hash
		>;

		std::unordered_map<std::string, shared_res<Texture2d>, string_hash, std::equal_to<>> textures;
	};
} // namespace gargantua::render
