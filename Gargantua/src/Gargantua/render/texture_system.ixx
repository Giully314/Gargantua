/*
* gargantua/render/texture_system.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* USAGE:	
* 
*/


export module gargantua.render.texture_system;

import <unordered_map>;
import <ranges>;
import <string>;

import gargantua.types;
import gargantua.render.texture2d;

namespace gargantua::render
{
	export 
	class TextureSystem : public Singleton<TextureSystem>
	{
	public:
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
		std::unordered_map<std::string, shared_res<Texture2d>> textures;
	};
} // namespace gargantua::render
