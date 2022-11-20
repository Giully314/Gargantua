/*
gargantua/render/render_utility.ixx

PURPOSE: Function utilities for temporary usage in testing.

CLASSES:
	Utility: struct with utility static methods.

DESCRIPTION:


*/

export module gargantua.render.render_utlity;

import <string_view>;

import gargantua.types;

import gargantua.render.element_buffer;
import gargantua.render.vertex_buffer;
import gargantua.render.vertex_array;
import gargantua.render.frame_buffer;
import gargantua.render.shader;
import gargantua.render.program;
import gargantua.render.texture2d;
import gargantua.render.render_types;


namespace gargantua::render
{

	export struct Utility
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

} //namespace gargantua::render

