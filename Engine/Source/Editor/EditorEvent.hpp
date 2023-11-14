#pragma once

#include "Runtime/Function/Event/EventCode.hpp"
#include "Runtime/Function/Event/EventStatus.hpp"

namespace RendererDemo {

class EditorEvent {
public:
    EditorEvent() = default;
    ~EditorEvent() = default;

    void Initialize();
    void Clear();

    void Tick();

private:
    void SyncEventStatus();

    bool IsKeyPressed(KeyboardCode code);

private:
    EventStatus m_event_status;
};

} // namespace RendererDemo
