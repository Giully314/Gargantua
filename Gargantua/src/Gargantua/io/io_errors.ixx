/*
* gargantua/io/io_errors.ixx
* 
* PURPOSE: Provide errors for io.
* 
* ENUMS:
*	FileError: errors for file related stuff.
*/

export module gargantua.io.errors;

import gargantua.types;

namespace gargantua::io
{
	export enum class FileError : u8
	{
		FileNotFound,
		Compile,
	};
} // namespace gargantua::io