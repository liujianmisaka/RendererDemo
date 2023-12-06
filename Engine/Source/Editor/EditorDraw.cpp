#include "Editor/EditorDraw.hpp"
#include <memory>
#include <filesystem>
#include "Runtime/Function/Framework/Component/MiniComponents.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Framework/FrameworkHeader.hpp"

namespace RendererDemo {

void EditorDraw::Initialize(EditorDrawInitInfo init_info) {
    m_rhi = init_info.rhi;
    m_game_world_manager = init_info.game_world_manager;
    m_editor_ui = init_info.editor_ui;

    InitDraw();
}

void EditorDraw::Clear(){};

void EditorDraw::Tick() { RuntimeDraw(); }

void EditorDraw::InitDraw() {
    std::filesystem::current_path("C:/dev/RendererDemo");

    std::shared_ptr<Scene> scene = m_game_world_manager->GetCurrentActivateScene();

    m_editor_ui->SetCamera(scene->GetSceneCamera());

    {
        Object object = scene->AddObject();
        auto& squa_component = object.AddComponent<SquaComponent>();
        auto& transform_component = object.AddComponent<TransformComponent>();
        // auto& mesh_component = object.AddComponent<MeshComponent>();
        // mesh_component.LoadModel("Asset/Model/stylized-popcorn-machine-lowpoly/source/SM_Popcorn Machine.fbx");
    }
}

void EditorDraw::RuntimeDraw(){};

} // namespace RendererDemo
