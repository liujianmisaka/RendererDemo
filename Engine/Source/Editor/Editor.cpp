#include "Editor/Editor.hpp"
#include <memory>
#include "Runtime/Engine.hpp"
#include "Runtime/RuntimeContext.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"

namespace RendererDemo {

void MisakaEditor::Initialize(RendererDemo::MisakaEngine* runtime_engine) {
    m_runtime_engine = runtime_engine;
    m_editor_draw = std::make_unique<EditorDraw>();
    m_editor_draw->Initialize();

    m_editor_event = std::make_unique<EditorEvent>();
    m_editor_event->Initialize();

    m_editor_ui = std::make_unique<EditorUI>();
    m_editor_ui->Initialize();
}

void MisakaEditor::Clear() {
    m_editor_ui->Clear();
    m_editor_draw->Clear();
    m_editor_event->Clear();
}

void MisakaEditor::Run() {
    while (true) {
        m_editor_event->Tick();
        m_editor_draw->Tick();
        while (!m_runtime_engine->Run()) {
            return;
        }
        m_editor_ui->Tick();

        // TODO: update in runtime
        g_runtime_context.m_window_system->SwapBuffers();
        g_runtime_context.m_window_system->PollEvents();
    }
}

} // namespace RendererDemo
