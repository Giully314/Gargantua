/*
* gargantua/input/input_inputsystem.ixx
* 
* PURPOSE: manage input.
* 
* CLASSES:
*	InputSystem: Manage keyboard and mouse.
* 
* DESCRIPTION:
*	This system is responsible to manage all the input functionalities and provide an access point for 
*	mouse and keyboard state.
* 
* USAGE:
*	auto& insys = InputSystem::Instance();
* 
*/

module;

#include <GLFW/glfw3.h>

export module gargantua.input.input_system;

import gargantua.types;
import gargantua.input.keyboard;
import gargantua.input.key_codes;
import gargantua.input.mouse;
import gargantua.input.mouse_codes;
import gargantua.math.vec2d;


namespace gargantua::input
{
	export class InputSystem : NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static
		auto Instance() -> InputSystem&
		{
			static InputSystem sys;
			return sys;
		}

		// Register listeners for all keyboard/mouse events.
		auto Startup() -> void;

		auto Shutdown() -> void
		{

		}


		auto Run() -> void
		{
			glfwPollEvents();
		}

		auto IsPressed(const Key key) const noexcept -> bool
		{
			return keyboard.IsPressed(key);
		}

		auto IsPressed(const MouseButton b) const noexcept -> bool
		{
			return mouse.GetButton(b);
		}

		auto GetMousePosition() const noexcept -> const math::Vec2df&
		{
			return mouse.GetPosition();
		}

	private:
		InputSystem() = default;

	private:
		Keyboard keyboard;
		Mouse mouse;
	};
} // namespace gargantua::input