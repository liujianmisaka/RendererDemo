#include "Editor/EditorDraw.hpp"
#include <memory>
#include <filesystem>
#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"
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

void EditorDraw::Tick() {
    RuntimeDraw();
}

void EditorDraw::InitDraw() {
    std::filesystem::current_path("C:/dev/RendererDemo");

    std::shared_ptr<GameWorldManager> game_world_manager = g_runtime_context.m_game_world_manager;
    {
        std::shared_ptr<Scene> scene = std::make_shared<Scene>();
        {
            std::shared_ptr<Object> object = std::make_shared<Object>();
            {
                std::shared_ptr<MeshComponent> component = std::make_shared<MeshComponent>();
                component->LoadModel("Asset/Model/stylized-popcorn-machine-lowpoly/source/SM_Popcorn Machine.fbx");
                object->AddComponent<MeshComponent>(component);
            }
            {
                std::shared_ptr<TransformComponent> component = std::make_shared<TransformComponent>();
                object->AddComponent<TransformComponent>(component);
            }
            {
                std::shared_ptr<CameraComponent> component = std::make_shared<CameraComponent>();
                object->AddComponent<CameraComponent>(component);
            }
            scene->AddObject("basic_object", object);
        }
        game_world_manager->AddScene("basic_scene", scene);
    }
}

void EditorDraw::RuntimeDraw(){};

} // namespace RendererDemo
