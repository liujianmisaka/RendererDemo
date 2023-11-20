#include "Editor/EditorEvent.hpp"
#include <iostream>
#include "Runtime/Function/Event/EventCode.hpp"
#include "Runtime/RuntimeContext.hpp"
#include "Runtime/Function/Event/EventSystem.hpp"

namespace RendererDemo {

void EditorEvent::Initialize() {
    SyncEventStatus();
}

void EditorEvent::Clear(){};

void EditorEvent::Tick() {
    SyncEventStatus();
    if (IsKeyPressed(KeyboardCode::A)) {
        std::cout << "A" << std::endl;
    }
}

void EditorEvent::SyncEventStatus() {
    m_event_status = g_runtime_context.m_event_system->GetEventStatus();
}

bool EditorEvent::IsKeyPressed(KeyboardCode code) {
    return m_event_status.keyboard_status[static_cast<int>(code)];
}

} // namespace RendererDemo
