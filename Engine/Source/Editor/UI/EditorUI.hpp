#pragma once

#include <cstdint>
#include "Editor/UI/SceneHierarchyPanel.hpp"

namespace RendererDemo {

class EditorUI {
public:
    EditorUI() = default;
    ~EditorUI() = default;

    void Initialize();
    void Clear();
    void Tick();

private:
    void Update();
    void BeginFrame();
    void ImGuiRender();
    void EndFrame();

    void RenderMenuBar();
    void RenderSettings();
    void RenderViewport();
    void RenderStatus();

    void SetDarkThemeColors();
    void SetFont();

private:
    uint64_t m_texture_id = 0;
    int m_width = 0;
    int m_height = 0;

    SceneHierarchyPanel m_scene_hierarchy_panel;
};

} // namespace RendererDemo
