/*
gargantua/logging/level.ixx

PURPOSE: Level of log.

CLASSES:
	Level: enum for enumerate the level of logging messages.

DESCRIPTION:

USAGE:

*/

export module gargantua.logging.log:level;


namespace gargantua::logging
{
	export enum class Level
	{
		debug = 0,   //For debug.
		info,		 //For information about the status of the program.
		warning,	 //The program could have some errors that leads to bugs/exceptions.
		error,		 //The program has serious errors that will interrupt the execution.
		off,		 //Turn off the logger.
	}; //enum class Level

} //namespace gargantua::logging