#include "Editor/EditorDraw.hpp"
#include <memory>
#include <filesystem>
#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"
#include "Runtime/Function/Framework/Component/Mesh/MeshComponent.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include "Runtime/Function/Renderer/RHI/RHI.hpp"
#include "Runtime/Function/RuntimeContext/RuntimeContext.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Framework/FrameworkHeader.hpp"

namespace RendererDemo {

void EditorDraw::Initialize() {
    m_rhi = g_runtime_context.m_renderer_system->GetRHI();

    InitDraw();
}

void EditorDraw::Clear(){};

void EditorDraw::Tick() { RuntimeDraw(); }

void EditorDraw::InitDraw() {
    std::filesystem::current_path("C:/dev/RendererDemo");

    std::shared_ptr<Scene> scene = g_runtime_context.m_game_world_manager->GetCurrentActivateScene();

    Object object = scene->CreateObject();
    {
        auto& mesh_component = scene->AddComponent<MeshComponent>(object);
        mesh_component.LoadModel("Asset/Model/stylized-popcorn-machine-lowpoly/source/SM_Popcorn Machine.fbx");

        auto& transform_component = scene->AddComponent<TransformComponent>(object);

        auto& camera_component = scene->AddComponent<CameraComponent>(object);
    }
}

void EditorDraw::RuntimeDraw(){};

} // namespace RendererDemo
