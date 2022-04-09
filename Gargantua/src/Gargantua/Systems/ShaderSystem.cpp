/*
Gargantua/Systems/ShaderSystem.cpp
*/
#include "ShaderSystem.hpp"

#include "Gargantua/Renderer/Types.hpp"

#include <algorithm>
#include <ranges>

namespace Gargantua
{
	namespace Systems
	{
		ShaderSystem::~ShaderSystem()
		{
			//I could set this in the destructor of shared_ptr
			std::ranges::for_each(std::views::values(cache), [](SharedRes<Renderer::Shader>& s)
				{
					s->Destroy();
				});
		}


		SharedRes<Renderer::Shader> ShaderSystem::GetShader(const std::string& filename)
		{
			//TODO: make it to use a transparent functor so avoid the contruction of a string for a look up.
			if (auto it = cache.find(filename); it != cache.end())
			{
				return it->second;
			}

			Renderer::ShaderType type;

			if (filename.find(".vert") != std::string::npos)
			{
				type = Renderer::ShaderType::vertex_shader;
			}
			else if (filename.find(".frag") != std::string::npos)
			{
				type = Renderer::ShaderType::fragment_shader;
			}
			else
			{
				//assert 
			}

			auto sh = CreateSharedRes<Renderer::Shader>();
			sh->Create(type);
			sh->Compile(shaders_filepath + filename);

			cache.emplace(filename, sh);

			return sh;
		}

		SharedRes<Renderer::Program> ShaderSystem::CreateProgram(const std::string& vert_filename, const std::string& frag_filename)
		{
			auto vsh = GetShader(vert_filename);
			auto fsh = GetShader(frag_filename);

			auto p = CreateSharedRes<Renderer::Program>();

			p->Create();
			p->Link(*vsh, *fsh);

			return p;
		}

	} //namespace Systems
} //namespace Gargantua