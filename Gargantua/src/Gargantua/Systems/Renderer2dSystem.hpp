#pragma once
/*
Gargantua/Systems/Renderer2dSystem.hpp

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

#include "Gargantua/Types.hpp"

#include "Gargantua/Math/Vec2d.hpp"
#include "Gargantua/Math/Vec4d.hpp"
#include "Gargantua/Math/Mat3d.hpp"

#include "Gargantua/Renderer/Texture2d.hpp"
#include "Gargantua/Renderer/Program.hpp"
#include "Gargantua/Renderer/VertexArray.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/OrthoCamera.hpp"
#include "Gargantua/Renderer/FrameBuffer.hpp"
#include "Gargantua/Renderer/RendererCommand.hpp"

#include "Gargantua/Systems/EventSystem.hpp"

#include <unordered_map>
#include <string>

namespace Gargantua
{
	namespace Systems
	{
		struct Renderer2dData
		{
			//This is the program that is executed for every draw call.
			SharedRes<Renderer::Program> program = nullptr;

			//This is the program that is executed to render the framebuffer.
			SharedRes<Renderer::Program> fb_program = nullptr;

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
			SharedRes<Renderer::VertexArray> va_quad = nullptr;
			SharedRes<Renderer::ElementBuffer> eb = nullptr;
			SharedRes<Renderer::Texture2d> tx_white = nullptr;
			
			SharedRes<Renderer::FrameBuffer> fb = nullptr;
			SharedRes<Renderer::VertexArray> fb_quad = nullptr;
			SharedRes<Renderer::ElementBuffer> fb_eb = nullptr;
			

			const Math::Vec4df white{ 1.0f, 1.0f, 1.0f, 1.0f };

			Math::Mat4df proj_view;
		};


		class Renderer2dSystem
		{
		public:
			Renderer2dSystem(natural_t width, natural_t height);


			void BeginScene(const Renderer::OrthoCamera& camera);
			void BeginScene(const Math::Mat4df& proj_view);
			void EndScene();


			void ListenAndRegisterEvents(SharedRes<Systems::EventSystem> event_sys);


			void DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size, 
				const Renderer::Texture2d& texture);

			void DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
				const Math::Vec4df& color);

			void DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
				const Math::Vec4df& color, const Renderer::Texture2d& texture);

			void DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
				const Renderer::Texture2d& texture, real_t tiling_factor);

			void DrawQuad(const Math::Vec2df& position, const Math::Vec2df& size,
				const Math::Vec4df& color, const Renderer::Texture2d& texture, real_t tiling_factor);



			void DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
				const Renderer::Texture2d& texture);

			void DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
				const Math::Vec4df& color);

			void DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
				const Math::Vec4df& color, const Renderer::Texture2d& texture);

			void DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
				const Renderer::Texture2d& texture, real_t tiling_factor);
		
			void DrawRotatedQuad(const Math::Vec2df& position, const Math::Vec2df& size, real_t rotation,
				const Math::Vec4df& color, const Renderer::Texture2d& texture, real_t tiling_factor);




			void SetCameraMatrix(Math::Mat4df camera_matrix)
			{
				data.proj_view = std::move(camera_matrix);
			}


			void SetProgram(SharedRes<Renderer::Program> program)
			{
				data.program = std::move(program);
			}

			void SetFBProgram(SharedRes<Renderer::Program> program)
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


			const Renderer::FrameBuffer& GetFrameBuffer() const 
			{
				return *data.fb;
			}

			void ResizeFrameBuffer(natural_t width, natural_t height)
			{
				data.fb->Resize(width, height);
				Renderer::RendererCommand::SetViewport(0, 0, width, height);
			}

		private:
			Renderer2dData data;
		};
	} //namespace Systems
} //namespace Gargantua