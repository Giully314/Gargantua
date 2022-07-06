#pragma once
/*
Gargantua/Renderer/Utility.hpp

PURPOSE: Function utilities for temporary usage in testing.

CLASSES:
	Utility: struct with utility static methods.

DESCRIPTION:
	

*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/VertexBuffer.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/VertexArray.hpp"
#include "Gargantua/Renderer/Texture2d.hpp"
#include "Gargantua/Renderer/Shader.hpp"
#include "Gargantua/Renderer/Program.hpp"
#include "Gargantua/Renderer/FrameBuffer.hpp"



namespace Gargantua
{
	namespace Renderer
	{
		struct Utility
		{
			static SharedRes<VertexBuffer> CreateVB();
			static SharedRes<VertexBuffer> CreateVB(const void* data, natural_t count, natural_t elem_per_vert, DrawMode mode);
			
			static SharedRes<ElementBuffer> CreateEB();
			static SharedRes<ElementBuffer> CreateEB(const void* data, natural_t count, DrawMode mode);
			
			static SharedRes<VertexArray> CreateVA();
			
			static SharedRes<Texture2d> CreateTX2d();
			static SharedRes<Texture2d> CreateTX2d(std::string_view file_name);
			static SharedRes<Texture2d> CreateTX2d(natural_t width, natural_t height, void* data);

			/*
			NOTE: these funcions are only for testing mode. For shader/program creation is better to use
			the ShaderManager.
			*/
			//Create Vertex Shader
			static SharedRes<Shader> CreateVSH(std::string_view path);
			//Create Fragment Shader
			static SharedRes<Shader> CreateFSH(std::string_view path);
			static SharedRes<Program> CreatePR(std::string_view vert_path, std::string_view frag_path);

			
			static SharedRes<FrameBuffer> CreateFB(natural_t width, natural_t height);
		};
	} //namespace Renderer 
} //namespace Gargantua

