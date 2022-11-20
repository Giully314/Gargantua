/*
gargantua/render/render_utility.cpp
*/

module gargantua.render.render_utlity;


import <utility>;


namespace gargantua::render
{

	//*************************** VERTEX BUFFER ********************************

	SharedRes<VertexBuffer> Utility::CreateVB()
	{
		auto vb = CreateSharedRes<VertexBuffer>();
		vb->Create();

		return vb;
	}


	SharedRes<VertexBuffer> Utility::CreateVB(const void* data, natural_t count, natural_t elem_per_vert, DrawMode mode)
	{
		auto vb = CreateSharedRes<VertexBuffer>();
		vb->Create();
		vb->Load(data, count, elem_per_vert, mode);

		return vb;
	}
	//*************************** VERTEX BUFFER ********************************


	//*************************** ELEMENT BUFFER ********************************

	SharedRes<ElementBuffer> Utility::CreateEB()
	{
		auto eb = CreateSharedRes<ElementBuffer>();
		eb->Create();

		return eb;
	}


	SharedRes<ElementBuffer> Utility::CreateEB(const void* data, natural_t count, DrawMode mode)
	{
		auto eb = CreateSharedRes<ElementBuffer>();
		eb->Create();
		eb->Load(data, count, mode);

		return eb;
	}
	//*************************** ELEMENT BUFFER ********************************


	//*************************** VERTEX ARRAY ********************************

	SharedRes<VertexArray> Utility::CreateVA()
	{
		auto va = CreateSharedRes<VertexArray>();
		va->Create();
		return va;
	}
	//*************************** VERTEX ARRAY ********************************


	//*************************** TEXTURE 2D ********************************

	SharedRes<Texture2d> Utility::CreateTX2d()
	{
		auto tx = CreateSharedRes<Texture2d>();
		tx->Create();

		return tx;
	}

	SharedRes<Texture2d> Utility::CreateTX2d(std::string_view file_name)
	{
		auto tx = CreateSharedRes<Texture2d>();
		tx->Create();
		tx->Load(file_name);

		return tx;
	}


	SharedRes<Texture2d> Utility::CreateTX2d(natural_t width, natural_t height, void* data)
	{
		auto tx = CreateSharedRes<Texture2d>();
		tx->Create();
		tx->Empty(width, height);
		tx->Fill(data);

		return tx;
	}
	//*************************** TEXTURE 2D ********************************


	//*************************** SHADER AND PROGRAM ********************************

	SharedRes<Shader> Utility::CreateVSH(std::string_view path)
	{
		auto vsh = CreateSharedRes<Shader>();
		vsh->Create(ShaderType::vertex_shader);
		vsh->Compile(path);
		return vsh;
	}

	SharedRes<Shader> Utility::CreateFSH(std::string_view path)
	{
		auto fsh = CreateSharedRes<Shader>();
		fsh->Create(ShaderType::fragment_shader);
		fsh->Compile(path);
		return fsh;
	}


	/*SharedRes<Program> Utility::CreatePR(std::string_view vert_path, std::string_view frag_path)
	{
		auto vsh = Utility::CreateVSH(vert_path);
		auto fsh = Utility::CreateFSH(frag_path);

		auto p = CreateSharedRes<Program>();
		p->Create();
		p->Link(*vsh, *fsh);

		vsh->Destroy();
		fsh->Destroy();
		return p;
	}*/
	//*************************** SHADER AND PROGRAM ********************************

	//*************************** FRAME BUFFER **************************************
	SharedRes<FrameBuffer> Utility::CreateFB(natural_t width, natural_t height)
	{
		auto fb = CreateSharedRes<FrameBuffer>();
		fb->Create();
		fb->Initialize(width, height);

		return fb;
	}
	//*************************** FRAME BUFFER **************************************

} //namespace gargantua::render