/*
gargantua/system/shader_system.cpp
*/

module gargantua.system.shader_system;

import <algorithm>;
import <ranges>;


import gargantua.render.render_types;

namespace gargantua::system
{

	ShaderSystem::~ShaderSystem()
	{
		//I could set this in the destructor of shared_ptr
		std::ranges::for_each(std::views::values(cache), [](SharedRes<render::Shader>& s)
			{
				s->Destroy();
			});
	}


	auto ShaderSystem::GetShader(const std::string& filename) -> SharedRes<render::Shader>
	{
		//TODO: make it to use a transparent functor so avoid the contruction of a string for a look up.
		if (auto it = cache.find(filename); it != cache.end())
		{
			return it->second;
		}

		render::ShaderType type;

		if (filename.find(".vert") != std::string::npos)
		{
			type = render::ShaderType::vertex_shader;
		}
		else if (filename.find(".frag") != std::string::npos)
		{
			type = render::ShaderType::fragment_shader;
		}
		else
		{
			//assert 
		}

		auto sh = CreateSharedRes<render::Shader>();
		sh->Create(type);
		sh->Compile(shaders_filepath + filename);

		cache.emplace(filename, sh);

		return sh;
	}

	auto ShaderSystem::CreateProgram(const std::string& vert_filename, const std::string& frag_filename) 
		-> SharedRes<render::Program>
	{
		auto vsh = GetShader(vert_filename);
		auto fsh = GetShader(frag_filename);

		auto p = CreateSharedRes<render::Program>();

		p->Create();
		p->Link(*vsh, *fsh);

		return p;
	}

} //namespace gargantua::system