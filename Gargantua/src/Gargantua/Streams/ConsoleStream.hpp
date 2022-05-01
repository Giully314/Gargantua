#pragma once
/*
Gargantua/Streams/ConsoleStream.hpp

PURPOSE: Console output stream.

CLASSES:
	ConsoleStream: std::cout wrapper class.

DESCRIPTION:
	This is a temporary class and should be used only for test.
*/

#include "Gargantua/Streams/StreamType.hpp"

#include <iostream>
#include <string>
#include <string_view>

namespace Gargantua
{
	namespace Streams
	{
		//To use ONLY for debug on local machine.
		class ConsoleStream
		{
		public:
			using StreamType = OutputStream;

			ConsoleStream& Flush()
			{
				std::cout.flush();
				return *this;
			}
		};

		inline ConsoleStream& operator<<(ConsoleStream& os, std::string_view s)
		{
			std::cout << s;
			return os;
		}
	} //namespace Streams
} //namespace Gargantua 