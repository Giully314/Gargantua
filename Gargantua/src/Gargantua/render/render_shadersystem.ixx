/*
* gargantua/render/render_shadersystem.ixx
* 
* PURPOSE: Provide singleton to manage access to shaders.
* 
* CLASSES:
*	ShaderSystem: Class for handling the creation/destruction of shaders.
* 
* DESCRIPTION:
*	This system provides a cache for shaders to avoid recompilation in case of multiple usages.
*/
module;

#include <gargantua/log/logger_macro.hpp>

export module gargantua.render.shader_system;

import <string_view>;
import <expected>;
import <stdexcept>;
import <unordered_map>;
import <string>;
import <functional>;
import <filesystem>;
import <tuple>;

import gargantua.types;
import gargantua.log;
import gargantua.render.shader;
import gargantua.io;

namespace gargantua::render
{
	export class ShaderSystem : private NonCopyable, NonMovable
	{
	public:

		static auto Instance() -> ShaderSystem&
		{
			static ShaderSystem shader_sys;
			return shader_sys;
		}


		// name is the path of the shader. 
		// The shader must be already in the cache or nullptr will be returned.
		[[nodiscard]]
		auto Get(const std::string_view name) -> non_owned_res<Shader>
		{
			auto r = shaders.find(name);
			// Operator [] for unordered_map using transparent is planned for C++23. 
			return r == shaders.end() ? nullptr : r->second.get();
		}


		/*
		* Load the shader located at path and return it.
		* The name of the shader saved in the cache is the same as the path.
		* Return: shared_ptr of the shader if no errors, 
		* otherwise resource::ResourceError::FileNotFound or resource::ResourceError::Compile
		*/
		[[nodiscard]]
		auto Load(std::filesystem::path path) 
			-> std::expected<non_owned_res<Shader>, io::FileError>
		{
			try
			{
				// TODO: is it the right place to deduce the type of the shader based on the file extension?
				auto ext = path.extension().string();
				auto shader_type = ext == ".frag" ? ShaderType::Fragment : ShaderType::Vertex;

				auto r = shaders.emplace(std::make_pair(path.string(), 
					CreateUniqueRes<Shader>(path, shader_type)));

				return r.first->second.get();
			}
			catch (std::invalid_argument&)
			{
				return std::unexpected(io::FileError::FileNotFound);
			}
			catch (std::runtime_error&)
			{
				return std::unexpected(io::FileError::Compile);
			}
		}


	private:
		ShaderSystem()
		{
			GRG_CORE_DEBUG("ShaderSystem startup.");
		}
	
	private:
		template <typename ...Bases>
		struct overload : Bases...
		{
			using is_transparent = void;
			using Bases::operator()...;
		};

		struct char_pointer_hash
		{
			auto operator()(const char* ptr) const noexcept
			{
				return std::hash<std::string_view>{}(ptr);
			}
		};

		using string_hash = overload<
			std::hash<std::string>,
			std::hash<std::string_view>,
			char_pointer_hash
		>;

		std::unordered_map<std::string, unique_res<Shader>, string_hash, std::equal_to<>> shaders;
	};

} // namespace gargantua::render