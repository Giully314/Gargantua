/*
* gargantua/render/renderer2d_system.ixx
* 
* PURPOSE: API for 2d rendering.
*
* CLASSES:
*	Renderer2dSystem: Singleton for 2d rendering using opengl commands.	
* 
* DESCRIPTION:
*	This module provides basic API for simple 2d rendering.
*	The 2d renderer works with batches. The draw calls stores the transformed vertex and are drawn at the end of the scene.
* 
* USAGE:
*	auto& renderer = Renderer2dSystem::Instance();
*	renderer.BeginScene(camera);
*	renderer.DrawQuad(position, size, color);
*	renderer.DrawQuad(position2, size2, texture2);
*	renderer.DrawRotatedQuad(position3, size3, rotation3, color3);
*	renderer.EndScene(); // Opengl draw calls are done here.
* 
* TODO:
*	- support for lines, circles.
*/

export module gargantua.render.renderer2d_system;

import <array>;

import gargantua.types;

import gargantua.render.buffer;
import gargantua.render.vertex_array;
import gargantua.render.program;
import gargantua.render.shader;
import gargantua.render.quad2d_batch;
import gargantua.render.quad2d_batch_system;
import gargantua.render.frame_buffer;
import gargantua.render.orthographic_camera;
import gargantua.render.texture2d;
import gargantua.render.subtexture2d;


import gargantua.math.matrix;
import gargantua.math.vector;

namespace gargantua::render
{
	struct FrameBufferData
	{
		Program program;
		VertexArray vao;
		VertexBuffer screen_vbo;
		VertexBuffer texture_vbo;
		FrameBuffer screen_fb;
	};

	// Keeps the info about the quad that it's used as primitive to draw.
	struct Quad2dData
	{
		Program program;
		Quad2dBatchSystem batch_system;
	};

	
	// Info about the (for now unique) source of light + ambient light.
	struct LightData
	{
		// program is the shader used to render the light source if visible.
		Program program;
		f32 ambient_strength{ 0.1f };
		math::Vec3df position;
		math::Vec4df color{ 1.0f, 1.0f, 1.0f, 1.0f };
	};


	export
	class Renderer2dSystem : private NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static
		auto Instance() -> Renderer2dSystem&
		{
			static Renderer2dSystem sys;
			return sys;
		}

		// Precondition: the opengl context must be usable.	
		auto Startup() -> void;
		auto Shutdown() -> void;

		
		// Setup the batches, set the camera.
		auto BeginScene(const math::Mat4df& camera) -> void;

		// Transform represents the position of the camera. 
		// It is inverted in the functio to obtain view.
		auto BeginScene(const math::Mat4df& transform, const math::Mat4df& projection) -> void;


		// Draw the batches.
		auto EndScene() -> void;

		// Resize the frame buffer and set the viewport.
		auto Resize(u32 width, u32 height) -> void;


		// Precondition: all draw calls must be done between BeginScene() and EndScene().

		
		auto DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
			const math::Vec4df& color) -> void;
		
		auto DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
			const shared_res<Texture2d>& texture, const f32 tiling_factor=1.0f) -> void;

		auto DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
			const SubTexture2d& subtexture, const f32 tiling_factor = 1.0f) -> void;

		auto DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, const f32 rotation,
			const math::Vec4df& color) -> void;

		auto DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, f32 rotation,
			const shared_res<Texture2d>& texture, const f32 tiling_factor = 1.0f) -> void;



		auto DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
			const math::Vec4df& color) -> void;

		auto DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
			const shared_res<Texture2d>& texture, const f32 tiling_factor = 1.0f) -> void;

		auto DrawQuad(const math::Vec3df& position, const math::Vec3df& size,
			const SubTexture2d& subtexture, const f32 tiling_factor = 1.0f) -> void;

		auto DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
			const math::Vec4df& color) -> void;

		auto DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
			const shared_res<Texture2d>& texture, const f32 tiling_factor = 1.0f) -> void;

		auto DrawRotatedQuad(const math::Vec3df& position, const math::Vec3df& size, const f32 rotation,
			const math::Vec4df& color,
			const shared_res<Texture2d>& texture, const f32 tiling_factor = 1.0f) -> void;


		auto RegisterLight(const math::Vec3df& position, const math::Vec4df color, f32 ambient_strength) -> void
		{
			light_data.position = position;
			light_data.color = color;
			light_data.ambient_strength = ambient_strength;
		}


		auto GetFrameBuffer() -> FrameBuffer&
		{
			return fb_data.screen_fb;
		}

	private:
		Renderer2dSystem() = default;
	
	private:
		FrameBufferData fb_data;
		Quad2dData data;
		LightData light_data;
		math::Mat4df camera;
	};

} // namespace gargantua::render
