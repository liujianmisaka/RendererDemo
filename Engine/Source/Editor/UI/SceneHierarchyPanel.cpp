#include "Editor/UI/SceneHierarchyPanel.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <cstdint>
#include <entt/entity/fwd.hpp>
#include "Editor/UI/Utils.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"
#include "Runtime/Function/Framework/Component/MiniComponents.hpp"

namespace RendererDemo {

SceneHierarchyPanel::SceneHierarchyPanel(const std::shared_ptr<Scene>& context) : m_scene(context) {}

void SceneHierarchyPanel::SetContext(const std::shared_ptr<Scene>& context) { m_scene = context; }

void SceneHierarchyPanel::OnImGuiRender() {
    ImGui::Begin("Scene Hierarchy");
    if (m_scene) {
        for (auto entity : m_scene->m_registry->view<TagComponent>()) {
            Object object = m_scene->GetObject(entity);

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
    auto& transform_component = object.GetComponent<TransformComponent>();
    auto roation = transform_component.GetRotation();
    auto position = transform_component.GetPosition();
    auto scale = transform_component.GetScale();
    DrawVec3Control("Rotation", roation);
    DrawVec3Control("Position", position);
    DrawVec3Control("Scale", scale, 1.0f);
    transform_component.SetRotation(roation);
    transform_component.SetPosition(position);
    transform_component.SetScale(scale);
}

} // namespace RendererDemo
