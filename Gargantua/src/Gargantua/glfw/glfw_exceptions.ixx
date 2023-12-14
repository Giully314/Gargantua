/*
* gargantua/glfw/glfw_exceptions.ixx
* 
* PURPOSE: exceptions for glfw related functions/class.
*/

export module gargantua.glfw.exceptions;

import <string_view>;
import <exception>;

namespace gargantua::glfw
{
	export class WindowConstructionError : public std::exception
	{
	public:
		explicit WindowConstructionError() : std::exception{ "Error constructing glfw window." }
		{

		}

		explicit WindowConstructionError(const std::string_view msg) : std::exception{msg.data()}
		{

		}
	};
} // namespace gargantua::glfw


