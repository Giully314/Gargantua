/*
* gargantua/platform/input_system.ixx
* 
* PURPOSE: manage I/O.
* 
* CLASSES:
*	InputSystem: Manage keyboard and mouse.
*/

module;

#include <GLFW/glfw3.h>

export module gargantua.platform.input_system;

import gargantua.types;
import gargantua.platform.event_dispatcher;
import gargantua.platform.keyboard;
import gargantua.platform.key_codes;
import gargantua.platform.mouse;
import gargantua.platform.mouse_codes;
import gargantua.platform.platform_events;
import gargantua.math.vec2d;


export namespace gargantua::platform
{
	class InputSystem : private NonCopyable, NonMovable
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

		auto IsPressed(Key key) const -> bool
		{
			return keyboard.IsPressed(key);
		}

		auto IsPressed(MouseButton b) const noexcept -> bool
		{
			return mouse.GetButton(b);
		}

		auto GetPosition() const noexcept -> const math::Vec2df&
		{
			return mouse.GetPosition();
		}

	private:
		InputSystem() = default;

	private:
		Keyboard keyboard;
		Mouse mouse;
	};
} // namespace gargantua::platform