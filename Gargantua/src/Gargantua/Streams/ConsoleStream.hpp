#pragma once

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
			//Maybe defines Tag structs for this
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