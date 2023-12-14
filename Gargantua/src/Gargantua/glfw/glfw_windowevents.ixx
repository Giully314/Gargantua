/*
* gargantua/glfw/glfw_windowevents.ixx
* 
* PURPOSE: define window related events.
* 
* CLASSES:
*	WindowResizeEvent: Stores the new size of the window after resize.
*	WindowCloseEvent: Stores the status of the window.
* 
*/

export module gargantua.glfw.window_events;

import gargantua.types;
import gargantua.event.base_event;


export namespace gargantua::glfw
{	
	struct WindowResizeEvent : event::BaseEvent
	{
		constexpr explicit WindowResizeEvent(const u32 new_width_, const u32 new_height_) :
			new_width(new_width_), new_height(new_height_)
		{

		}

		const u32 new_width;
		const u32 new_height;
	};


	struct WindowCloseEvent : event::BaseEvent
	{
		constexpr explicit WindowCloseEvent(const bool is_closed_) : is_closed(is_closed_)
		{

		}

		const bool is_closed;
	};
} // namespace gargantua::glfw