/*
* gargantua/render/subtexture2d.ixx
* 
* PURPOSE: Manage 2d subtexture.
* 
* CLASSES:
*	SubTexture2d: manage a texture2d used for multiple subtextures.
*/

export module gargantua.render.subtexture2d;

import <array>;
import <span>;

import gargantua.types;
import gargantua.render.texture2d;
import gargantua.math.vec2d;


namespace gargantua::render
{
	export
	class SubTexture2d
	{
	public:
		SubTexture2d(const shared_res<Texture2d>& texture_, math::Vec2df coords, math::Vec2df cell_size,
			math::Vec2df sprite_size = { 1.0f, 1.0f }) : texture(texture_)
		{
			auto width = texture->GetWidth();
			auto height = texture->GetHeight();

			math::Vec2df min = { coords.x * cell_size.x / width, coords.y * cell_size.y / height };
			math::Vec2df max = { (coords.x + sprite_size.x) * cell_size.x / width, (coords.y + sprite_size.y) * cell_size.y / height };


			text_coords[0] = { max.x, max.y };
			text_coords[1] = { max.x, min.y };
			text_coords[2] = { min.x, min.y};
			text_coords[3] = { min.x, max.y };
		}

		auto GetTexture() const -> const shared_res<Texture2d>&
		{
			return texture;
		}


		auto GetCoords() const -> const std::span<const math::Vec2df>
		{
			return std::span{ text_coords };
		}

	private:
		shared_res<Texture2d> texture;
		std::array<math::Vec2df, 4> text_coords;
	};

} // namespace gargantua::render
