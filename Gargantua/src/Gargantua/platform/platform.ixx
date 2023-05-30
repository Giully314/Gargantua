/*
* gargantua/platform/platform.ixx 
* 
* DESCRIPTION:
*	The module platform define and initialize all the things that are inherent to the platform on which
*	the engine runs. Basically it is a layer of communication between the Engine and the low level
*	resources such as the Window, I/O, memory and so on.
*/

export module gargantua.platform.platform;

export import gargantua.platform.event_dispatcher;
export import gargantua.platform.platform_events;
export import gargantua.platform.window;
export import gargantua.platform.keyboard;
export import gargantua.platform.key_codes;
export import gargantua.platform.mouse;
export import gargantua.platform.mouse_codes;
export import gargantua.platform.input_system;
export import gargantua.platform.platform_system;
export import gargantua.platform.imgui_system;