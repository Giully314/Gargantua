/*
* gargantua/platform/imgui_system.ixx
* 
* PURPOSE: Manage ImGui integration.
* 
* CLASSES:
*	ImGuiSystem: Manage all the glue code for the integration of ImGui in the engine.
*/

export module gargantua.platform.imgui_system;


import gargantua.types;

import gargantua.platform.window;

namespace gargantua::platform
{
	export
	class ImGuiSystem : private NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static 
		auto Instance() -> ImGuiSystem&
		{
			static ImGuiSystem sys;
			return sys;
		}

		auto Startup(non_owned_res<Window> window) -> void;

		auto Shutdown() -> void;

		auto BeginScene() -> void;
		auto EndScene() -> void;

	private:
		ImGuiSystem() = default;

	private:
		non_owned_res<Window> window;
	};

} // namespace gargantua::platform
