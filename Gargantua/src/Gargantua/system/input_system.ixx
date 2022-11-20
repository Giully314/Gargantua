/*
gargantua/system/input_systems.ixx

PURPOSE: Handle the inputs.

CLASSES:
	InputSystem: Keep the state of keyboard and mouse.


DESCRIPTION:
	This class keeps the state of inputs using events of GLFW. The state is "locked" at the
	start of every frame;
	this means that events of the engine are processed at the start of the game loop and the
	state of the input is updated and ready to be used for the current frame.
*/

export module gargantua.system.input_system;

import gargantua.types;

import gargantua.input.keyboard;
import gargantua.input.mouse;

import gargantua.event.event_listener_manager;

import gargantua.system.event_system;

import gargantua.math.vec2d;


namespace gargantua::system
{

	export class InputSystem
	{
	public:
		InputSystem();

		//TODO: change the dependency of event system
		auto ListenAndRegisterEvents(SharedRes<system::EventSystem> event_sys) -> void; 

		static auto IsPressed(key_t key) noexcept -> bool
		{
			return keyboard->GetKey(key);
		}

		static auto MouseCoords() noexcept -> math::Vec2df
		{
			return math::Vec2df{ mouse->GetX(), mouse->GetY() };
		}


		static auto ResetState() -> void
		{
			keyboard->ResetState();
			mouse->ResetState();
		}


	private:
		static UniqueRes<input::KeyboardState> keyboard;
		static UniqueRes<input::MouseState> mouse;
	};

} //namespace gargantua::system