/*
gargantua/system/renderer2d_system.ixx

PURPOSE: 2d rendering API.

CLASSES:
	Renderer2dData: Set of data used by the renderer.

	Renderer2dSystem: Class for handling 2d draw calls.


DESCRIPTION:
	Basic functionalities for rendering any object with 2d conventions.
	The basic geometric figures that can be rendered are: quad.



USAGE:
	Renderer2dSystem renderer2d{window_witdh, window_height};

	renderer2d.SetProgram(program);
	renderer2d.SetUniform("camera", "my_camera_uniform_name_inside_the_shader");

	renderer2d.BeginScene(camera_matrix);

	renderer2d.DrawQuad(position1, scale1, color1);
	renderer2d.DrawRotatedQuad(position2, scale2, rotation, color2, texture);


TODO:
	maybe make the functions template to allow different types of vec?
	Other basic geometries: point, line, triangle, circle.
	Set a background image.
	Draw single pixels.
*/

export module gargantua.system.renderer2d_system;

import <unordered_map>;
import <string>;

import gargantua.types;

import gargantua.math.vector;
import gargantua.math.mat4d;

import gargantua.render.texture2d;
import gargantua.render.vertex_array;
import gargantua.render.element_buffer;
import gargantua.render.program;
import gargantua.render.renderer_command;
import gargantua.render.frame_buffer;

import gargantua.system.event_system;


namespace gargantua::system
{

	struct Renderer2dData
	{
		//This is the program that is executed for every draw call.
		SharedRes<render::Program> program = nullptr;

		//This is the program that is executed to render the framebuffer.
		SharedRes<render::Program> fb_program = nullptr;

		/*
		This map allows the user to set the name of the uniform associated to the various variable
		inside the shader.
		In this way there is a lot of flexibility and respect for the name conventions used by the user.

		uniforms["camera"] = name_of_the_uniform_associated_to_the_camera;
		uniforms["transform"] = same_thing;
		*/
		std::unordered_map<std::string, std::string> uniforms;


		//These are used for simplify the process of drawing a simple quad.
		//In a 2d renderer, most of the time, a quad is the only shape used for drawing.
		SharedRes<render::VertexArray> va_quad = nullptr;
		SharedRes<render::ElementBuffer> eb = nullptr;
		SharedRes<render::Texture2d> tx_white = nullptr;

		SharedRes<render::FrameBuffer> fb = nullptr;
		SharedRes<render::VertexArray> fb_quad = nullptr;
		SharedRes<render::ElementBuffer> fb_eb = nullptr;


		const math::Vec4df white{ 1.0f, 1.0f, 1.0f, 1.0f };

		math::Mat4df proj_view;
	}; //struct Renderer2dData


	export class Renderer2dSystem
	{
	public:
		Renderer2dSystem(natural_t width, natural_t height);


		void BeginScene(const math::Mat4df& proj_view);
		void EndScene();


		void ListenAndRegisterEvents(SharedRes<system::EventSystem> event_sys);


		void DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
			const render::Texture2d& texture);

		void DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
			const math::Vec4df& color);

		void DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
			const math::Vec4df& color, const render::Texture2d& texture);

		void DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
			const render::Texture2d& texture, real_t tiling_factor);

		void DrawQuad(const math::Vec2df& position, const math::Vec2df& size,
			const math::Vec4df& color, const render::Texture2d& texture, real_t tiling_factor);



		void DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
			const render::Texture2d& texture);

		void DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
			const math::Vec4df& color);

		void DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
			const math::Vec4df& color, const render::Texture2d& texture);

		void DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
			const render::Texture2d& texture, real_t tiling_factor);

		void DrawRotatedQuad(const math::Vec2df& position, const math::Vec2df& size, real_t rotation,
			const math::Vec4df& color, const render::Texture2d& texture, real_t tiling_factor);




		void SetCameraMatrix(math::Mat4df camera_matrix)
		{
			data.proj_view = std::move(camera_matrix);
		}


		void SetProgram(SharedRes<render::Program> program)
		{
			data.program = std::move(program);
		}

		void SetFBProgram(SharedRes<render::Program> program)
		{
			data.fb_program = std::move(program);
		}

		/*
		Responsability of the caller to pass a valid type name.
		type name could be: "camera", "transform".
		*/
		void SetUniform(const std::string& type, const std::string& uniform_name)
		{
			data.uniforms[type] = uniform_name;
		}


		const render::FrameBuffer& GetFrameBuffer() const
		{
			return *data.fb;
		}

		void ResizeFrameBuffer(natural_t width, natural_t height)
		{
			data.fb->Resize(width, height);
			render::RendererCommand::SetViewport(0, 0, width, height);
		}

	private:
		Renderer2dData data;
	}; //class Renderer2dSystem

} //namespace gargantua::system