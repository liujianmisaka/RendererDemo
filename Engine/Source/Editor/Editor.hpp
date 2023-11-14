#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Editor/EditorDraw.hpp"
#include "Editor/EditorEvent.hpp"
#include "Editor/EditorUI.hpp"

namespace RendererDemo {

class EditorDraw;
class EditorEvent;

class MisakaEngine;

class MisakaEditor {
public:
    void Initialize(RendererDemo::MisakaEngine* runtime_engine);
    void Clear();

    void Run();

private:
    RendererDemo::MisakaEngine* m_runtime_engine = nullptr;
    std::unique_ptr<EditorDraw> m_editor_draw = nullptr;
    std::unique_ptr<EditorEvent> m_editor_event = nullptr;
    std::unique_ptr<EditorUI> m_editor_ui = nullptr;
};

} // namespace RendererDemo
