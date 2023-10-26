/*
* gargantua/render/shader_system.ixx
* 
* PURPOSE: Manage shaders.
* 
* CLASSES:
*	ShaderSystem: 
* 
* DESCRIPTION:
* 
* 
*/

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
import gargantua.render.shader;
import gargantua.resource;

namespace gargantua::render
{
	export 
	class ShaderSystem : private NonCopyable, NonMovable
	{
	public:

		static auto Instance() -> ShaderSystem&
		{
			static ShaderSystem shader_sys;
			return shader_sys;
		}


		// name is the path of the shader. If not present, the shader will be loaded.
		[[nodiscard]]
		auto Get(std::string_view name) -> non_owned_res<Shader>
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
		auto Load(std::filesystem::path path) -> std::expected<non_owned_res<Shader>, resource::ResourceError>
		{
			try
			{
				// TODO: is it the right place to deduce the type of the shader based on the file extension?
				auto ext = path.extension().string();
				auto shader_type = ext == ".frag" ? ShaderType::Fragment : ShaderType::Vertex;

				auto r = shaders.emplace(std::make_pair(path.string(), CreateUniqueRes<Shader>(path, shader_type)));

				return r.first->second.get();
			}
			catch (std::invalid_argument&)
			{
				return std::unexpected(resource::ResourceError::FileNotFound);
			}
			catch (std::runtime_error&)
			{
				return std::unexpected(resource::ResourceError::Compile);
			}
		}


	private:
		ShaderSystem() = default;
	
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