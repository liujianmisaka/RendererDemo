#include "Editor/UI/SceneHierarchyPanel.hpp"
#include <imgui.h>
#include <cstdint>
#include <entt/entity/fwd.hpp>
#include "Runtime/Function/Framework/Object/SceneCamera.hpp"
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
    auto& scene_camera = m_scene->GetSceneCamera();
    auto type = scene_camera.GetProjectionType();
    if (type == ProjectionType::Perspective) {
        auto fov = scene_camera.GetPerspectiveFOV();
        if (ImGui::DragFloat("Perspective FOV", &fov)) {
            scene_camera.SetPerspectiveFOV(fov);
        }
        auto near = scene_camera.GetPerspectiveNear();
        if (ImGui::DragFloat("Perspective Near", &near)) {
            scene_camera.SetPerspectiveNear(near);
        }
        auto far = scene_camera.GetPerspectiveFar();
        if (ImGui::DragFloat("Perspective Far", &far)) {
            scene_camera.SetPerspectiveFar(far);
        }
    } else if (type == ProjectionType::Orthographic) {
        auto size = scene_camera.GetOrthographicSize();
        if (ImGui::DragFloat("Orthographic Size", &size)) {
            scene_camera.SetOrthographicSize(size);
        }
        auto near = scene_camera.GetOrthographicNear();
        if (ImGui::DragFloat("Orthographic Near", &near)) {
            scene_camera.SetOrthographicNear(near);
        }
        auto far = scene_camera.GetOrthographicFar();
        if (ImGui::DragFloat("Orthographic Far", &far)) {
            scene_camera.SetOrthographicFar(far);
        }
    }
}

} // namespace RendererDemo
