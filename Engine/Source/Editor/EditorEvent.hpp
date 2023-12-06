#pragma once

#include <memory>
#include "Runtime/Function/Event/EventCode.hpp"
#include "Runtime/Function/Event/EventStatus.hpp"
#include "Runtime/Function/Event/EventSystem.hpp"

namespace RendererDemo {

class EditorEvent {
public:
    EditorEvent() = default;
    ~EditorEvent() = default;

    void Initialize(std::shared_ptr<EventSystem> event_system);
    void Clear();

    void Tick();

private:
    void SyncEventStatus();

    bool IsKeyPressed(KeyboardCode code);

private:
    std::shared_ptr<EventSystem> m_event_system = nullptr;
    EventStatus m_event_status;
};

} // namespace RendererDemo
