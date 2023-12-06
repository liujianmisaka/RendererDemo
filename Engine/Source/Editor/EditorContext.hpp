#pragma once

#include "Editor/EditorDraw.hpp"
#include "Editor/EditorEvent.hpp"
#include "Editor/UI/EditorUI.hpp"
#include "Runtime/Engine.hpp"

namespace RendererDemo {

class EditorContext {
public:
    EditorContext() = default;
    ~EditorContext() = default;

    void StartEditorSystem(RendererDemo::MisakaEngine* runtime_engine);
    void ShutdownEditorSystem();

public:
    std::shared_ptr<EditorDraw> m_editor_draw = nullptr;
    std::shared_ptr<EditorEvent> m_editor_event = nullptr;
    std::shared_ptr<EditorUI> m_editor_ui = nullptr;
    RendererDemo::MisakaEngine* m_runtime_engine = nullptr;
};

} // namespace RendererDemo
