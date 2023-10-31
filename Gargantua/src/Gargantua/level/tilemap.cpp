/*
* gargantua/level/tilemap.cpp
*/

module gargantua.level.tilemap;


namespace gargantua::level
{
	auto TileMap::Render() -> void
	{
		auto& rend = render::Renderer2dSystem::Instance();
		if (background)
		{
			// TODO: this is not correct. This call must be immediate or be elaborated with a different API
			// because the rendering of the background is not the same as the rendering of entities.
			rend.DrawQuad(position, { 1, 1 }, background);
		}
	}
} // namespace gargantua::level