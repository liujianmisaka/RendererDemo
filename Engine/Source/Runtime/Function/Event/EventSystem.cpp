#include "Runtime/Function/Event/EventSystem.hpp"
#include "Runtime/Function/Event/EventCode.hpp"
#include "Runtime/Function/Event/EventStatus.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"

namespace RendererDemo {

void EventSystem::Initialize(std::shared_ptr<WindowSystem> window_system) {
    m_window_system = window_system;
    AddGetStatusHandlers();
}

void EventSystem::Clear(){};

void EventSystem::Tick() {
    m_event_delegate.Broadcast();
}

EventStatus EventSystem::GetEventStatus() {
    return m_event_status;
}

void EventSystem::AddEventHandlers(std::function<void()> func) {
    m_event_delegate.Add(func);
}

bool EventSystem::MouseStatus(MouseCode code) const {
    return m_event_status.mouse_status[static_cast<int>(code)];
}

bool EventSystem::KeyboardStatus(KeyboardCode code) const {
    return m_event_status.keyboard_status[static_cast<int>(code)];
}

bool EventSystem::KeyboardRepeatStatus(KeyboardCode code) const {
    return m_event_status.keyboard_repeat_status[static_cast<int>(code)];
}

bool EventSystem::WindowStatus(WindowEvent code) const {
    return m_event_status.window_status[static_cast<int>(code)];
}

void EventSystem::SetMouseStatus(MouseCode code, bool status) {
    m_event_status.mouse_status[static_cast<int>(code)] = status;
}

void EventSystem::SetKeyboardStatus(KeyboardCode code, bool status) {
    m_event_status.keyboard_status[static_cast<int>(code)] = status;
}

void EventSystem::SetKeyboardRepeatStatus(KeyboardCode code, bool status) {
    m_event_status.keyboard_repeat_status[static_cast<int>(code)] = status;
}

void EventSystem::SetWindowStatus(WindowEvent code, bool status) {
    m_event_status.window_status[static_cast<int>(code)] = status;
}

void EventSystem::AddGetStatusHandlers() {
    /* -------------------------------------------------------------------------- */
    /*                             Default GLFW Event                             */
    /* -------------------------------------------------------------------------- */
    m_window_system->AddTransactionHandler<TransactionType::WindowClose>(
        [this](GLFWwindow* window) { SetWindowStatus(WindowEvent::Close, true); });

    m_window_system->AddTransactionHandler<TransactionType::WindowResize>(
        [this](GLFWwindow* window, int width, int height) { SetWindowStatus(WindowEvent::Resize, true); });

    m_window_system->AddTransactionHandler<TransactionType::KeyPressed>(
        [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
            // WARING: Use GLFW code as RendererDemo code
            SetKeyboardStatus(static_cast<KeyboardCode>(key), true);
        });

    m_window_system->AddTransactionHandler<TransactionType::KeyRepeated>(
        [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
            // WARING: Use GLFW code as RendererDemo code
            SetKeyboardStatus(static_cast<KeyboardCode>(key), true);
        });

    m_window_system->AddTransactionHandler<TransactionType::KeyReleased>(
        [this](GLFWwindow* window, int key, int scancode, int action, int mods) {
            // WARING: Use GLFW code as RendererDemo code
            SetKeyboardStatus(static_cast<KeyboardCode>(key), false);
            SetKeyboardRepeatStatus(static_cast<KeyboardCode>(key), false);
        });

    m_window_system->AddTransactionHandler<TransactionType::MouseButtonPressed>(
        [this](GLFWwindow* window, int button, int action, int mods) {
            // WARING: Use GLFW code as RendererDemo code
            SetWindowStatus(static_cast<WindowEvent>(button), true);
        });

    m_window_system->AddTransactionHandler<TransactionType::MouseButtonReleased>(
        [this](GLFWwindow* window, int button, int action, int mods) {
            // WARING: Use GLFW code as RendererDemo code
            SetWindowStatus(static_cast<WindowEvent>(button), false);
        });
}

} // namespace RendererDemo
