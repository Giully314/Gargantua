#pragma once
/*
Gargantua/Renderer/RendererCommand.hpp


PURPOSE: Info about a submit renderer call.

CLASSES:
	RendererCommand: struct with info about a draw call or a instruction to renderer.

DESCRIPTION:
	

*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/Types.hpp"
#include "Gargantua/Renderer/VertexArray.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/Program.hpp"


namespace Gargantua
{
	namespace Renderer
	{
		struct RendererCommand
		{
			NonOwnedRes<VertexArray> va;
			NonOwnedRes<ElementBuffer> eb;
			NonOwnedRes<Program> program;
			RenderTopology topology;
		};
	} //namespace Renderer
} //namespace Gargantua