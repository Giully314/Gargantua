#pragma once
/*
Gargantua/Systems/ShaderSystem.hpp

PURPOSE: Manage shader cache.


CLASSES:
	ShaderSystem: Handle the creation of the shaders and programs.

DESCRIPTION:
	This systems does basically 2 things: create shaders and link them into a program.
	The shaders are stored into a cache for reuse. 


USAGE:
	ShaderSystem s;

	UniqueRes<Program> p = s.CreateProgram("vertex_shader.vert", "fragment_shader.frag");

*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Renderer/Shader.hpp"
#include "Gargantua/Renderer/Program.hpp"

#include <unordered_map>
#include <string>

namespace Gargantua
{
	namespace Systems
	{
		class ShaderSystem
		{
		public:

			~ShaderSystem();

			SharedRes<Renderer::Shader> GetShader(const std::string& filename);
			
			SharedRes<Renderer::Program> CreateProgram(const std::string& vert_filename, const std::string& frag_filename);

		private:
			std::unordered_map<std::string, SharedRes<Renderer::Shader>> cache;
			std::string shaders_filepath = "Shaders/";
		};
	} //namespace Systems 
} //namespace Gargantua