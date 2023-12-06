#include "Editor/Editor.hpp"
#include <memory>

namespace RendererDemo {

void MisakaEditor::Initialize(RendererDemo::MisakaEngine* runtime_engine) {
    m_editor_context.StartEditorSystem(runtime_engine);
}

void MisakaEditor::Clear() { m_editor_context.ShutdownEditorSystem(); }

void MisakaEditor::Run() {
    while (true) {
        m_editor_context.m_editor_event->Tick();
        m_editor_context.m_editor_draw->Tick();
        while (!m_editor_context.m_runtime_engine->Run()) {
            return;
        }

        m_editor_context.m_editor_ui->Tick();
    }
}

} // namespace RendererDemo
