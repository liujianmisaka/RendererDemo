#include "Editor/UI/SceneHierarchyPanel.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <cstdint>
#include <entt/entity/fwd.hpp>
#include "Editor/UI/Utils.hpp"
#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"
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
    object.HasComponent<TagComponent>();
    ImGui::Text("Tag Component");
    auto& tag_component = object.GetComponent<TagComponent>();
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strcpy_s(buffer, sizeof(buffer), tag_component.GetTag().c_str());
    if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
        tag_component.SetTag(std::string(buffer));
    }

    if (object.HasComponent<TransformComponent>()) {
        ImGui::Separator();
        ImGui::Text("Transform Component");
        auto& transform_component = object.GetComponent<TransformComponent>();

        auto roation = transform_component.GetRotation();
        DrawVec3Control("Rotation", roation);
        transform_component.SetRotation(roation);

        auto position = transform_component.GetPosition();
        DrawVec3Control("Position", position);
        transform_component.SetPosition(position);

        auto scale = transform_component.GetScale();
        DrawVec3Control("Scale", scale, glm::vec3(1.0f));
        transform_component.SetScale(scale);
    }

    if (object.HasComponent<CameraComponent>()) {
        ImGui::Separator();
        ImGui::Text("Camera Component");
        auto& camera_component = object.GetComponent<CameraComponent>();
        auto position = camera_component.GetCamera().GetPosition();
        DrawVec3Control("Position", position);
        camera_component.GetCamera().SetPosition(position);

        auto rotation = camera_component.GetCamera().GetRotation();
        DrawVec3Control("Rotation", rotation);
        camera_component.GetCamera().SetRotation(rotation);

        auto aspect_ratio = camera_component.GetCamera().GetAspectRatio();
        if (ImGui::DragFloat("Aspect Ratio", &aspect_ratio)) {
            camera_component.GetCamera().SetAspectRatio(aspect_ratio);
        }

        auto fov = camera_component.GetCamera().GetFov();
        if (ImGui::DragFloat("Perspective FOV", &fov)) {
            camera_component.GetCamera().SetFov(fov);
        }
        auto near = camera_component.GetCamera().GetNearClip();
        if (ImGui::DragFloat("Perspective Near", &near)) {
            camera_component.GetCamera().SetNearClip(near);
        }
        auto far = camera_component.GetCamera().GetFarClip();
        if (ImGui::DragFloat("Perspective Far", &far)) {
            camera_component.GetCamera().SetFarClip(far);
        }
    }
}

} // namespace RendererDemo
