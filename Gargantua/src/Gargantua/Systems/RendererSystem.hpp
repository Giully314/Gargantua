#pragma once
/*
Gargantua/Systems/RendererSystem.hpp

PURPOSE: Renderer API.


CLASSES:
	RenderSystem: System with low level API for rendering an object.


DESCRIPTION:
	The rendering system is used to make low level rendering calls. 
	For example a Renderer2dSystem could be built using this system as base block.
	One import thing to note about the design is that the submit call is not a draw call.
	A submit call is just passing data to form a RendererCommand to be executed later.
	The update of the frame is done inside the engine game loop using RenderFrame().

TODO:
	I would like to use the same approach for the PhysicsSystem.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/OrthoCamera.hpp"
#include "Gargantua/Renderer/VertexArray.hpp"
#include "Gargantua/Renderer/Texture2d.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/Program.hpp"
#include "Gargantua/Renderer/Types.hpp"

#include "Gargantua/Math/Vec4d.hpp"

#include "Gargantua/Event/EventListenerManager.hpp"

#include <vector>

namespace Gargantua
{
	namespace Systems
	{
		class RendererSystem
		{
		public:
			RendererSystem(natural_t width, natural_t height);

			void BeginScene(NonOwnedRes<Renderer::OrthoCamera> camera);
			void EndScene();


			void ListenToEvents(NonOwnedRes<Event::EventListenerManager> event_list_mng);

			void RenderFrame();

			void SetClearColor(const Math::Vec4df& color);

			void Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
				NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t) const;

			void Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
				NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t, const Math::Mat4df& transform) const;

			void Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
				NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t, 
				NonOwnedRes<Renderer::Texture2d> texture) const;

			void Submit(NonOwnedRes<Renderer::VertexArray> va, NonOwnedRes<Renderer::ElementBuffer> eb,
				NonOwnedRes<Renderer::Program> p, Renderer::RenderTopology t,
				NonOwnedRes<Renderer::Texture2d> texture, const Math::Mat4df& transform) const;
		
		private:
			NonOwnedRes<Renderer::OrthoCamera> camera;
		};
	} //namespace Systems
} //namespace Gargantua