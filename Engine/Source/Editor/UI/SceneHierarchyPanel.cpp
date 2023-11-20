#include "Editor/UI/SceneHierarchyPanel.hpp"
#include <imgui.h>
#include <cstdint>
#include <entt/entity/fwd.hpp>
#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"
#include "Runtime/Function/Framework/Component/Component.hpp"

namespace RendererDemo {

SceneHierarchyPanel::SceneHierarchyPanel(const std::shared_ptr<Scene>& context) : m_scene(context) {}

void SceneHierarchyPanel::SetContext(const std::shared_ptr<Scene>& context) { m_scene = context; }

void SceneHierarchyPanel::OnImGuiRender() {
    ImGui::Begin("Scene Hierarchy");
    if (m_scene) {
        for (auto entity : m_scene->m_registry->view<TagComponent>()) {
            Object object(entity, m_scene);

            std::string tag = object.GetComponent<TagComponent>().GetTag();
            ImGui::PushID(static_cast<uint32_t>(object));
            if (ImGui::Selectable(tag.c_str())) {
                m_scene->m_selected_object = object;
            }
            ImGui::PopID();
        }
    }
    ImGui::End();

    ImGui::Begin("Properties");
    if (m_scene && m_scene->m_selected_object) {
        DrawComponentsofObject(m_scene->m_selected_object);
    }
    ImGui::End();
}

void SceneHierarchyPanel::DrawComponentsofObject(Object object) {
    // if (object.HasComponent<TagComponent>()) {
    //     auto& tag = object.GetComponent<TagComponent>().GetTag();
    //     char buffer[256];
    //     memset(buffer, 0, sizeof(buffer));
    //     strcpy_s(buffer, sizeof(buffer), tag.c_str());
    // }
}

} // namespace RendererDemo
