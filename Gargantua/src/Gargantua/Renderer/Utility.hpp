#pragma once
/*
Gargantua/Renderer/Utility.hpp

PURPOSE: Function utilities.

CLASSES:
	Utility: struct with utility static methods.

DESCRIPTION:
	

*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/VertexBuffer.hpp"
#include "Gargantua/Renderer/ElementBuffer.hpp"
#include "Gargantua/Renderer/VertexArray.hpp"
#include "Gargantua/Renderer/Texture2d.hpp"
#include "Gargantua/Renderer/OrthoCamera.hpp"
#include "Gargantua/Renderer/Shader.hpp"
#include "Gargantua/Renderer/Program.hpp"
#include "Gargantua/Renderer/FrameBuffer.hpp"



namespace Gargantua
{
	namespace Renderer
	{
		struct Utility
		{
			static UniqueRes<VertexBuffer> CreateVB();
			static UniqueRes<VertexBuffer> CreateVB(const void* data, natural_t count, natural_t elem_per_vert, BufferElementType type, DrawMode mode);
		
			static UniqueRes<ElementBuffer> CreateEB();
			static UniqueRes<ElementBuffer> CreateEB(const void* data, natural_t count, BufferElementType type, DrawMode mode);
		
			static UniqueRes<VertexArray> CreateVA();

			static UniqueRes<Texture2d> CreateTX2d();
			static UniqueRes<Texture2d> CreateTX2d(std::string_view file_name);
			static UniqueRes<Texture2d> CreateTX2d(natural_t width, natural_t height, void* data);
			

			static UniqueRes<OrthoCamera> CreateOrtho(real_t l, real_t b, real_t r, real_t t, real_t n, real_t f);
			static UniqueRes<OrthoCamera> CreateOrtho(real_t l, real_t b, real_t r, real_t t);
			static UniqueRes<OrthoCamera> CreateOrtho(natural_t width, natural_t height);
			static UniqueRes<OrthoCamera> CreateOrtho(natural_t width, natural_t height, real_t cam_value);

			/*
			NOTE: these funcions are only for testing mode. For shader/program creation is better to use
			the ShaderManager.
			*/
			//Create Vertex Shader
			static UniqueRes<Shader> CreateVSH(std::string_view path);
			//Create Fragment Shader
			static UniqueRes<Shader> CreateFSH(std::string_view path);
			static UniqueRes<Program> CreatePR(std::string_view vert_path, std::string_view frag_path);

			
			static UniqueRes<FrameBuffer> CreateFB(natural_t width, natural_t height);
		};
	} //namespace Renderer 
} //namespace Gargantua

