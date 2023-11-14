#pragma once

#include <cstdint>

namespace RendererDemo {

class EditorUI {
public:
    EditorUI() = default;
    ~EditorUI() = default;

    void Initialize();
    void Clear();

    void Update();

    void BeginFrame();
	void ImGuiDraw();
    void EndFrame();

    void Tick();

    void SetTexture(uint64_t texture_id);

private:
    void SetDarkThemeColors();

private:
    uint64_t m_texture_id = 0;
    int m_width = 0;
    int m_height = 0;
};

} // namespace RendererDemo
