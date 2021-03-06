#pragma once
/*
Gargantua/Log/Level.hpp

PURPOSE: Level of log.

CLASSES:
	Level: enum for enumerate the level of logging messages.

DESCRIPTION:

USAGE:

*/

namespace Gargantua
{
	namespace Log
	{
		enum class Level
		{
			debug = 0,   //For debug.
			info,		 //For information about the status of the program.
			warning,	 //The program could have some errors that leads to bugs/exceptions.
			error,		 //The program has serious errors that will interrupt the execution.
			off,		 //Turn off the logger.
		};
	} //namespace Log
} //namespace Gargantua