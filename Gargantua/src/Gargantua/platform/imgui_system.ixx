/*
* gargantua/platform/imgui_system.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
*/

export module gargantua.platform.imgui_system;


import gargantua.types;

import gargantua.platform.window;

namespace gargantua::platform
{
	export
	class ImGuiSystem : public Singleton<ImGuiSystem>
	{
	public:
		auto Startup(non_owned_res<Window> window) -> void;

		auto Shutdown() -> void;

		auto BeginScene() -> void;
		auto EndScene() -> void;

	private:
		non_owned_res<Window> window;
	};

} // namespace gargantua::platform
