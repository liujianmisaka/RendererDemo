#pragma once

#include "Runtime/Function/Renderer/System/WindowSystem.hpp"

namespace RendererDemo {

// 事件基类
class EventSystem {
public:
    EventSystem() = default;
    ~EventSystem() = default;

    void Initialize(std::shared_ptr<WindowSystem> window_system);
    void Clear();

private:
    void AddHandlers();

private:
    std::shared_ptr<WindowSystem> m_window_system = nullptr;
};

} // namespace RendererDemo
