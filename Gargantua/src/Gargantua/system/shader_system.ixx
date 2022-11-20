/*
gargantua/system/shader_system.ixx

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

export module gargantua.system.shader_system;

import <unordered_map>;
import <string>;

import gargantua.types;

import gargantua.render.shader;
import gargantua.render.program;


namespace gargantua::system
{

	export class ShaderSystem
	{
	public:

		~ShaderSystem();

		auto GetShader(const std::string& filename) ->SharedRes<render::Shader>;

		auto CreateProgram(const std::string& vert_filename, const std::string& frag_filename) 
			-> SharedRes<render::Program>;

	private:
		std::unordered_map<std::string, SharedRes<render::Shader>> cache;
		std::string shaders_filepath = "Shaders/";
	};

} //namespace gargantua::system