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
		auto GetFromFile(const std::string& name) -> shared_res<Texture2d>
		{
			if (textures.contains(name))
			{
				return textures[name];
			}

			// Load texture.
			auto texture = CreateSharedRes<Texture2d>();
			texture->Load(name);
			textures[name] = texture;

			return texture;
		}

		/*
		* Get a texture with the given name. If not present, create an empty new one.
		*/
		[[nodiscard]]
		auto Get(const std::string& name) -> shared_res<Texture2d>
		{
			if (textures.contains(name))
			{
				return textures[name];
			}

			auto texture = CreateSharedRes<Texture2d>();
			textures[name] = texture;
			return texture;
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
		std::unordered_map<std::string, shared_res<Texture2d>> textures;
	};
} // namespace gargantua::render
