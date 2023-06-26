/*
* editor/editor_gui.ixx
* 
* PURPOSE: GUI for the editor.
* 
* CLASSES:
*	EditorGUI: stage for the gui of the editor.
* 
* DESCRIPTION:
*	The EditorGUI is a stage that manages the gui interactions. The user can add/remove entities,
*	modify components and interact in a practical way with the game creation.
* 
*/

module;

#include <imgui.h>
#include <imgui_internal.h>
//#include <misc/cpp/imgui_stdlib.h>

export module gargantua.editor.editor_gui;

import <string_view>;
import <string>;
import <vector>;
import <typeinfo>;
import <array>;
import <concepts>;

import gargantua;

namespace gargantua::editor
{
	export 
	class EditorGUI : public app::Stage
	{
	public:
		EditorGUI(non_owned_res<scene::SceneContext> context_) : app::Stage("EditorGUI"),
			context(context_)
		{

		}

		auto Startup() -> void override;

		auto RenderGUI() -> void override;

	private:
		// TODO: concepts for types
		template <typename T, typename F>
			requires std::invocable<F, T&>
		auto ShowComponent(std::string_view name, scene::Entity e, F&& f) -> void
		{
			const ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_DefaultOpen | 
				ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | 
				ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
			if (e.Has<T>())
			{
				auto& component = e.Get<T>();
				ImVec2 content_region_avail = ImGui::GetContentRegionAvail();

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
				float line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
				ImGui::Separator();
				bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), tree_node_flags, name.data());
				ImGui::PopStyleVar();
				ImGui::SameLine(content_region_avail.x - line_height * 0.5f);
				if (ImGui::Button("+", ImVec2{ line_height, line_height }))
				{
					ImGui::OpenPopup("component_settings");
				}
				
				// TODO: show better.
				bool remove_component = false;
				if (ImGui::BeginPopup("component_settings"))
				{
					if (ImGui::MenuItem("Remove component"))
						remove_component = true;

					ImGui::EndPopup();
				}

				if (open)
				{
					f(component);
					ImGui::TreePop();
				}

				if (remove_component)
				{
					e.Erase<T>();
				}
			}
		}


		auto EntityNode() -> void;
		auto ShowComponents(scene::Entity e) -> void;
		

		auto AddComponentNode() -> void;


	private:
		non_owned_res<scene::SceneContext> context;
		scene::Entity entity_selected;

		const ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow |
			ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
	
		
		const std::array<const std::string_view, 4> component_names = {
			"Tag", "Transform", "Camera", "Texture",
		};
	};
} // namespace gargantua




