#pragma once

#include <memory>
#include <imgui.h>
#include "Editor/UI/AssetPanel.hpp"
#include "Editor/UI/LogPanel.hpp"
#include "Editor/UI/SceneHierarchyPanel.hpp"
#include "Runtime/Function/Framework/Component/Camera/Camera.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"

namespace RendererDemo {

struct EditorUIInitInfo {
    std::shared_ptr<WindowSystem> window_system;
    std::shared_ptr<RendererSystem> renderer_system;
    std::shared_ptr<GameWorldManager> game_world_manager;
};

class EditorUI {
public:
    EditorUI() = default;
    ~EditorUI() = default;

    void Initialize(EditorUIInitInfo init_info);
    void Clear();
    void Tick();

    void SetCamera(const Camera& camera) { m_camera = camera; }

private:
    void UIInit();

    void Update();
    void BeginFrame();
    void ImGuiRender();
    void EndFrame();

    void RenderMenuBar();
    void RenderSettings();
    void RenderViewport();

    void SetDarkThemeColors();
    void SetFont();

private:
    ImVec2 m_viewport_size = ImVec2(0, 0);

    std::shared_ptr<WindowSystem> m_window_system;
    std::shared_ptr<RendererSystem> m_renderer_system;
    std::shared_ptr<GameWorldManager> m_game_world_manager;

    SceneHierarchyPanel m_scene_hierarchy_panel;
    AssetPanel m_asset_panel;
    LogPanel m_log_panel;

    Camera m_camera;

    ImTextureID m_texture_id;
};

} // namespace RendererDemo
