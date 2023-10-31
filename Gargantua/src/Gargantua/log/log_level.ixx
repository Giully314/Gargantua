/*
gargantua/log/level.ixx

PURPOSE: Level of log.

CLASSES:
	Level: enum for enumerate the level of logging messages.
*/

export module gargantua.log.logger:level;

import gargantua.types;

namespace gargantua::log
{
	export
	enum class Level : u8
	{
		debug = 0,   //For debug.
		info,		 //For information about the status of the program.
		warning,	 //The program could have some errors that leads to bugs/exceptions.
		error,		 //The program has serious errors that will interrupt the execution.
		off,		 //Turn off the logger.
	}; 
} //namespace gargantua::log