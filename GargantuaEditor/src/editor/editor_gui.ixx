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
import <vector>;
import <typeinfo>;

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
		auto ShowComponent(std::string_view name, scene::Entity e, F&& f) -> void
		{
			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | 
				ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | 
				ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
			if (e.Has<T>())
			{
				auto& component = e.Get<T>();
				ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
				ImGui::Separator();
				bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.data());
				ImGui::PopStyleVar();
				ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
				if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
				{
					ImGui::OpenPopup("ComponentSettings");
				}
				
				// TODO: show better.
				bool removeComponent = false;
				if (ImGui::BeginPopup("ComponentSettings"))
				{
					if (ImGui::MenuItem("Remove component"))
						removeComponent = true;

					ImGui::EndPopup();
				}

				if (open)
				{
					f(component);
					ImGui::TreePop();
				}

				if (removeComponent)
					e.Erase<T>();
			}
		}


		auto CameraNode() -> void;
		auto EntityNode() -> void;


		auto ShowComponents(ecs::entity_t e) -> void;

	private:
		non_owned_res<scene::SceneContext> context;
		ecs::entity_t entity_selected = ecs::null_entity;

		const ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow |
			ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
	};
} // namespace gargantua




