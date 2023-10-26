/*
* gargantua/resource/resource_errors.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
*/

export module gargantua.resource.errors;

export 
namespace gargantua::resource
{
	enum class ResourceError
	{
		FileNotFound,
		Compile,
	};
} // namespace gargantua::resource