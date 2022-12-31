/*
gargantua/system/system.ixx

PURPOSE: describe what is a system and the characteristic.



DESCRIPTION:
	A system is the composition of one or more component into a "glue" class that manages to fusion
	the single functionalities of the components into a whole, more complex, functionality.
	But basically a system is a class that provides some sort of "services".
	For example the ResourceSystem is a struct with only static methods that provides functions
	for loading resources.
	The EventSystem is the composition of multiple components of the Event namespace that allows
	to form an event system.
*/

export module gargantua.system.system;


export import gargantua.system.event_system;
export import gargantua.system.input_system;
export import gargantua.system.logger_system;
export import gargantua.system.renderer2d_system;
export import gargantua.system.resource_system;
export import gargantua.system.shader_system;
export import gargantua.system.time_system;