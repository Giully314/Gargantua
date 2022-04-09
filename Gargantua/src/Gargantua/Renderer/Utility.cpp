/*
Gargantua/Renderer/Utility.cpp
*/
#include "Utility.hpp"
#include "Gargantua/Renderer/Types.hpp"

namespace Gargantua
{
	namespace Renderer
	{
		//*************************** VERTEX BUFFER ********************************

		UniqueRes<VertexBuffer> Utility::CreateVB()
		{
			auto vb = CreateUniqueRes<VertexBuffer>();
			vb->Create();

			return vb;
		}


		UniqueRes<VertexBuffer> Utility::CreateVB(const void* data, natural_t count, natural_t elem_per_vert, BufferElementType type, DrawMode mode)
		{
			auto vb = CreateUniqueRes<VertexBuffer>();
			vb->Create();
			vb->Load(data, count, elem_per_vert, type, mode);

			return vb;
		}
		//*************************** VERTEX BUFFER ********************************


		//*************************** ELEMENT BUFFER ********************************

		UniqueRes<ElementBuffer> Utility::CreateEB()
		{
			auto eb = CreateUniqueRes<ElementBuffer>();
			eb->Create();

			return eb;
		}


		UniqueRes<ElementBuffer> Utility::CreateEB(const void* data, natural_t count, BufferElementType type, DrawMode mode)
		{
			auto eb = CreateUniqueRes<ElementBuffer>();
			eb->Create();
			eb->Load(data, count, type, mode);

			return eb;
		}
		//*************************** ELEMENT BUFFER ********************************


		//*************************** VERTEX ARRAY ********************************

		UniqueRes<VertexArray> Utility::CreateVA()
		{
			auto va = CreateUniqueRes<VertexArray>();
			va->Create();
			return va;
		}
		//*************************** VERTEX ARRAY ********************************


		//*************************** TEXTURE 2D ********************************

		UniqueRes<Texture2d> Utility::CreateTX2d()
		{
			auto tx = CreateUniqueRes<Texture2d>();
			tx->Create();

			return tx;
		}

		UniqueRes<Texture2d> Utility::CreateTX2d(std::string_view file_name)
		{
			auto tx = CreateUniqueRes<Texture2d>();
			tx->Create();
			tx->Load(file_name);

			return tx;
		}


		UniqueRes<Texture2d> Utility::CreateTX2d(natural_t width, natural_t height, void* data)
		{
			auto tx = CreateUniqueRes<Texture2d>();
			tx->Create();
			tx->Empty(width, height);
			tx->SetColor(data);

			return tx;
		}
		//*************************** TEXTURE 2D ********************************
		


		//*************************** ORTHO CAMERA ********************************

		UniqueRes<OrthoCamera> Utility::CreateOrtho(real_t l, real_t b, real_t r, real_t t, real_t n, real_t f)
		{
			auto cam = CreateUniqueRes<OrthoCamera>(l, b, r, t, n, f);
			return cam;
		}


		UniqueRes<OrthoCamera> Utility::CreateOrtho(real_t l, real_t b, real_t r, real_t t)
		{
			auto cam = CreateUniqueRes<OrthoCamera>(l, b, r, t);
			return cam;
		}


		UniqueRes<OrthoCamera> Utility::CreateOrtho(natural_t width, natural_t height)
		{
			real_t aspect_ratio = (real_t)width / (real_t)height;

			real_t cam_value = 5.0f;
			real_t b = -cam_value;
			real_t t = cam_value;
			real_t r = cam_value * aspect_ratio;
			real_t l = -r;

			auto cam = CreateUniqueRes<OrthoCamera>(l, b, r, t);
			return cam;
		}


		UniqueRes<OrthoCamera> Utility::CreateOrtho(natural_t width, natural_t height, real_t cam_value)
		{
			real_t aspect_ratio = (real_t)width / (real_t)height;

			real_t b = -cam_value;
			real_t t = cam_value;
			real_t r = cam_value * aspect_ratio;
			real_t l = -r;

			auto cam = CreateUniqueRes<OrthoCamera>(l, b, r, t);
			return cam;
		}
		//*************************** ORTHO CAMERA ********************************
		

		//*************************** SHADER AND PROGRAM ********************************

		UniqueRes<Shader> Utility::CreateVSH(std::string_view path)
		{
			auto vsh = CreateUniqueRes<Shader>();
			vsh->Create(ShaderType::vertex_shader);
			vsh->Compile(path);
			return vsh;
		}
		
		UniqueRes<Shader> Utility::CreateFSH(std::string_view path)
		{
			auto fsh = CreateUniqueRes<Shader>();
			fsh->Create(ShaderType::fragment_shader);
			fsh->Compile(path);
			return fsh;
		}


		UniqueRes<Program> Utility::CreatePR(std::string_view vert_path, std::string_view frag_path)
		{
			auto vsh = Utility::CreateVSH(vert_path);
			auto fsh = Utility::CreateFSH(frag_path);

			auto p = CreateUniqueRes<Program>();
			p->Create();
			p->Link(*vsh, *fsh);

			vsh->Destroy();
			fsh->Destroy();
			return p;
		}
		//*************************** SHADER AND PROGRAM ********************************

		//*************************** FRAME BUFFER **************************************
		UniqueRes<FrameBuffer> Utility::CreateFB(natural_t width, natural_t height)
		{
			auto fb = CreateUniqueRes<FrameBuffer>();
			fb->Create();
			fb->Initialize(width, height);

			return fb;
		}
		//*************************** FRAME BUFFER **************************************

	} //namespace Renderer 
} //namespace Gargantua