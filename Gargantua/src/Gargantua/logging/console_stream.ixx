/*
Gargantua/Streams/ConsoleStream.hpp

PURPOSE: Console output stream.

CLASSES:
	ConsoleStream: std::cout wrapper class.

DESCRIPTION:
	This is a temporary class and should be used only for test.
*/

export module gargantua.logging.log:console_stream;

import <iostream>;
import <string_view>;

import :stream_type;

namespace gargantua::logging
{
	//To use ONLY for debug on local machine.
	export class ConsoleStream
	{
	public:
		using StreamType = OutputStreamTag;

		auto Flush() -> ConsoleStream&
		{
			std::cout.flush();
			return *this;
		}
	}; //class ConsoleStream

	export inline ConsoleStream& operator<<(ConsoleStream& os, std::string_view s)
	{
		std::cout << s;
		return os;
	}

} //namespace gargantua::logging