#include "Editor/EditorDraw.hpp"
#include <memory>
#include <filesystem>
#include "Runtime/Function/Framework/Component/Mesh/MeshComponent.hpp"
#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Framework/FrameworkHeader.hpp"

namespace RendererDemo {

void EditorDraw::Initialize(std::shared_ptr<RHI> rhi, std::shared_ptr<GameWorldManager> game_world_manager) {
    m_rhi = rhi;
    m_game_world_manager = game_world_manager;

    InitDraw();
}

void EditorDraw::Clear(){};

void EditorDraw::Tick() { RuntimeDraw(); }

void EditorDraw::InitDraw() {
    std::filesystem::current_path("C:/dev/RendererDemo");

    std::shared_ptr<Scene> scene = m_game_world_manager->GetCurrentActivateScene();

    Object object = scene->CreateObject();
    {
        auto& mesh_component = object.AddComponent<MeshComponent>();
        mesh_component.LoadModel("Asset/Model/stylized-popcorn-machine-lowpoly/source/SM_Popcorn Machine.fbx");
        auto& transform_component = object.AddComponent<TransformComponent>();
    }
}

void EditorDraw::RuntimeDraw(){};

} // namespace RendererDemo
