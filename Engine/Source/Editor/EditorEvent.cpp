#include "Editor/EditorEvent.hpp"
#include <iostream>

namespace RendererDemo {

void EditorEvent::Initialize(std::shared_ptr<EventSystem> event_system) {
    m_event_system = event_system;
    SyncEventStatus();
}

void EditorEvent::Clear(){};

void EditorEvent::Tick() {
    SyncEventStatus();
    if (IsKeyPressed(KeyboardCode::A)) {
        std::cout << "A" << std::endl;
    }
}

void EditorEvent::SyncEventStatus() { m_event_status = m_event_system->GetEventStatus(); }

bool EditorEvent::IsKeyPressed(KeyboardCode code) { return m_event_status.keyboard_status[static_cast<int>(code)]; }

} // namespace RendererDemo
