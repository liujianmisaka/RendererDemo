#include "Editor/UI/LogPanel.hpp"
#include <imgui.h>

namespace RendererDemo {

void LogPanel::OnImGuiRender() {
    ImGui::Begin("Log");
    ImGui::Text("Log");
    ImGui::End();
}

} // namespace RendererDemo
