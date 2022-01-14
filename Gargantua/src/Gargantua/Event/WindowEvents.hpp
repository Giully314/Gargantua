#pragma once

#include "Gargantua/Types.hpp"
#include "Gargantua/Event/BaseEvent.hpp"


//TODO: Window input focus, window focus, window refresh, 


namespace Gargantua
{
	namespace Event
	{
		struct WindowResizeEvent : public BaseEvent
		{
			WindowResizeEvent(natural_t new_width_, natural_t new_height_) :
				new_width(new_width_), new_height(new_height_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME

			const natural_t new_width;
			const natural_t new_height;
		};


		struct WindowCloseEvent : public BaseEvent
		{
			WindowCloseEvent(bool is_closed_) : is_closed(is_closed_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME

			const bool is_closed;
		};
	} //namespace Event 
} //namespace Gargantua