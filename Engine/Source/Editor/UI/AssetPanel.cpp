#include "Editor/UI/AssetPanel.hpp"
#include <imgui.h>

namespace RendererDemo {

void AssetPanel::OnImGuiRender() {
    ImGui::Begin("Asset");
    ImGui::Text("Asset");
    ImGui::End();
}

} // namespace RendererDemo
