#pragma once

#include <functional>
#include <memory>
#include "Runtime/Core/Handler/Delegate.hpp"
#include "Runtime/Function/Event/EventStatus.hpp"
#include "Runtime/Function/Event/EventCode.hpp"

namespace RendererDemo {

class WindowSystem;

// 事件基类
class EventSystem {
public:
    EventSystem() = default;
    ~EventSystem() = default;

    void Initialize(std::shared_ptr<WindowSystem> window_system);
    void Clear();

    void Tick();

    EventStatus GetEventStatus();
    void AddEventHandlers(std::function<void()> func);

    bool MouseStatus(MouseCode code) const;
    bool KeyboardStatus(KeyboardCode code) const;
    bool KeyboardRepeatStatus(KeyboardCode code) const;
    bool WindowStatus(WindowEvent code) const;

private:
    void SetMouseStatus(MouseCode code, bool status);
    void SetKeyboardStatus(KeyboardCode code, bool status);
    void SetKeyboardRepeatStatus(KeyboardCode code, bool status);
    void SetWindowStatus(WindowEvent code, bool status);

    void AddGetStatusHandlers();

    // TODO: Add a transaction function from GLFW Event to RendererDemo Event, now use glfwcode as RendererDemo code

private:
    std::shared_ptr<WindowSystem> m_window_system = nullptr;
    EventStatus m_event_status{};
    Delegate<> m_event_delegate{};
};

} // namespace RendererDemo
