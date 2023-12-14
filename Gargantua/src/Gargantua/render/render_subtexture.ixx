/*
* gargantua/render/render_subtexture.ixx
* 
* PURPOSE: Provide implementation of subTexture.
* 
* CLASSES:
*	SubTexture: manage a Texture used for multiple subtextures.
* 
* DESCRIPTION:
* 
* USAGE:
*
* 
* TODO:
*	- I don't think it's right to pass a shared_res to the subtexture.
*/

export module gargantua.render.subtexture;

import <array>;
import <span>;

import gargantua.types;
import gargantua.render.texture;
import gargantua.math.vec2d;


namespace gargantua::render
{
	export class SubTexture
	{
	public:
		explicit SubTexture(const shared_res<Texture>& texture_, const math::Vec2df coords, const math::Vec2df cell_size,
			math::Vec2df sprite_size = math::Vec2df{ 1.0f, 1.0f }) : texture(texture_)
		{
			using namespace math;

			auto width = texture->Width();
			auto height = texture->Height();

			Vec2df min { coords.x * cell_size.x / width, coords.y * cell_size.y / height };
			Vec2df max { (coords.x + sprite_size.x) * cell_size.x / width, (coords.y + sprite_size.y) * cell_size.y / height };

			text_coords[0] = Vec2df{ max.x, max.y };
			text_coords[1] = Vec2df{ max.x, min.y };
			text_coords[2] = Vec2df{ min.x, min.y};
			text_coords[3] = Vec2df{ min.x, max.y };
		}

		auto MainTexture() const -> const shared_res<Texture>&
		{
			return texture;
		}

		auto Coords() const -> const std::span<const math::Vec2df>
		{
			return std::span{ text_coords };
		}

	private:
		shared_res<Texture> texture;
		std::array<math::Vec2df, 4> text_coords;
	};
} // namespace gargantua::render
