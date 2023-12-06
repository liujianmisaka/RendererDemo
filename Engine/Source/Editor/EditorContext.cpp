#include "Editor/EditorContext.hpp"

namespace RendererDemo {

void EditorContext::StartEditorSystem(RendererDemo::MisakaEngine* runtime_engine) {
    m_runtime_engine = runtime_engine;

    auto runtime_context = runtime_engine->GetRuntimeContext();
    m_editor_draw = std::make_unique<EditorDraw>();
    m_editor_event = std::make_unique<EditorEvent>();
    m_editor_ui = std::make_unique<EditorUI>();

    m_editor_draw->Initialize(runtime_context.m_renderer_system->GetRHI(), runtime_context.m_game_world_manager);

    m_editor_event->Initialize(runtime_context.m_event_system);

    EditorUIInitInfo editor_ui_init_info;
    editor_ui_init_info.window_system = runtime_context.m_window_system;
    editor_ui_init_info.renderer_system = runtime_context.m_renderer_system;
    editor_ui_init_info.game_world_manager = runtime_context.m_game_world_manager;
    m_editor_ui->Initialize(editor_ui_init_info);
}

void EditorContext::ShutdownEditorSystem() {
    m_editor_ui->Clear();
    m_editor_draw->Clear();
    m_editor_event->Clear();
}

} // namespace RendererDemo
