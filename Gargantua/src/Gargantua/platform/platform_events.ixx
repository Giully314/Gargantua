/*
* gargantua/platform/platform_events.ixx
* 
* PURPOSE: Define all the platform events.
* 
* CLASSES:
*	BaseEvent: Base class of all events. Used to recognize events in the concept Event.
*	KeyEvent: A key event. Stores the key code.
*	KeyPressedEvent: Information about the key pressed.
*	KeyReleasedEvent: Information about the key released.
*	WindowResizeEvent: Stores the new size of the window after resize.
*	WindowCloseEvent: Stores the status of the window.
*	MouseCursorEvent: Stores the new position of the cursor.
*	MouseButtonEvent: Stores the mouse button code.
*	MouseButtonPressedEvent: Information about the mouse button pressed.
*	MouseButtonReleasedEvent: Information about the mouse button released.
*	MouseWheelScrollEvent: Stores the offset of the wheel.
*	ImGuiEvent: ImGui event base.
*	ImGuiPanelResizeEvent: Information about the resize of the imgui panel.
* 
* CONCEPTS:
*	Event: Check if a class is derived from the BaseEvent. Used to check a compile time if the type passed to the event dispatcher
*			is a proper event.
* 
* DESCRIPTION:
*	In this file there are the definitions of all the events releated to the platform. These are events about the state of the window and 
*	the inputs from keyboard and mouse.
* 
*/

export module gargantua.platform.platform_events;

import <concepts>;

import gargantua.types;
import gargantua.platform.key_codes;
import gargantua.platform.mouse_codes;


export namespace gargantua::platform
{
	struct BaseEvent
	{ };

	template <typename T>
	concept Event = std::derived_from<T, BaseEvent>;
	

	// **************** KEY EVENTS **********************************

	struct KeyEvent : public BaseEvent
	{
		KeyEvent(const Key key_) : key(key_)
		{

		}

		const Key key;
	};

	struct KeyPressedEvent : public KeyEvent
	{
		KeyPressedEvent(const Key key) : KeyEvent(key)
		{

		}
	};


	struct KeyReleasedEvent : public KeyEvent
	{
		KeyReleasedEvent(const Key key) : KeyEvent(key)
		{

		}
	};
	
	// **************** KEY EVENTS **********************************



	// **************** WINDOW EVENTS **********************************

	struct WindowResizeEvent : public BaseEvent 
	{
		WindowResizeEvent(const u32 new_width_, const u32 new_height_) :
			new_width(new_width_), new_height(new_height_)
		{

		}
		
		const u32 new_width;
		const u32 new_height;
	};


	struct WindowCloseEvent : public BaseEvent
	{
		WindowCloseEvent(const bool is_closed_) : is_closed(is_closed_)
		{

		}

		const bool is_closed;
	};

	// **************** WINDOW EVENTS **********************************



	// **************** MOUSE EVENTS **********************************

	struct MouseCursorEvent : public BaseEvent
	{
		MouseCursorEvent(const f32 x_, const f32 y_) : x(x_), y(y_)
		{

		}


		const f32 x;
		const f32 y;
	};


	struct MouseButtonEvent : public BaseEvent
	{
		MouseButtonEvent(MouseButton button_) : button(button_)
		{
		}

		const MouseButton button;
	}; 


	struct MouseButtonPressedEvent : public MouseButtonEvent
	{
		MouseButtonPressedEvent(const MouseButton button_) : MouseButtonEvent(button_)
		{

		}
	}; 

	struct MouseButtonReleasedEvent : public MouseButtonEvent
	{
		MouseButtonReleasedEvent(const MouseButton button_) : MouseButtonEvent(button_)
		{

		}
	}; 


	struct MouseWheelScrollEvent : public BaseEvent
	{
		MouseWheelScrollEvent(const f32 y_offset_) : y_offset(y_offset_)
		{

		}

		const f32 y_offset;
	}; 

	// **************** MOUSE EVENTS **********************************

	// ****************** IMGUI EVENTS ********************************

	struct ImGuiEvent : public BaseEvent
	{
		
	};
	
	struct ImGuiPanelResizeEvent : public ImGuiEvent
	{
		ImGuiPanelResizeEvent(u32 new_width_, u32 new_height_) :
			new_width(new_width_), new_height(new_height_)
		{

		}

		const u32 new_width;
		const u32 new_height;
	};

	// ****************** IMGUI EVENTS ********************************

} // namespace gargantua::platform