#pragma once

#include "Runtime/Engine.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"
namespace RendererDemo {

class EditorContext {
public:
    EditorContext() = default;
    ~EditorContext() = default;

    void Initialize();
    void Clear();

public:
    class RendererSystem *m_renderer_system = nullptr;
    class WindowSystem *m_window_system = nullptr;
    class MisakaEngine *m_runtime_engine = nullptr;
};

} // namespace RendererDemo
