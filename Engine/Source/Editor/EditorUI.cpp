#include "Editor/EditorUI.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include "Runtime/Function/RuntimeContext/RuntimeContext.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"
#include "Runtime/Function/Renderer/RHI/RHI.hpp"

namespace RendererDemo {

void EditorUI::Initialize() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Init imgui docking
    GLFWwindow* window = g_runtime_context.m_window_system->GetNativeWindow();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    g_runtime_context.m_renderer_system->GetRHI()->GetTextureOfRenderResult(m_texture_id);
}

void EditorUI::Clear() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditorUI::Update() {
    m_width = g_runtime_context.m_window_system->GetWidth();
    m_height = g_runtime_context.m_window_system->GetHeight();
}

void EditorUI::BeginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void EditorUI::ImGuiDraw() {
    // 创建一个 ImGui Viewport
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    // ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::Begin("Viewport");
    ImGui::Image((void*)(intptr_t)m_texture_id, ImVec2(m_width, m_height), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void EditorUI::EndFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorUI::Tick() {
	Update();
	BeginFrame();
	ImGuiDraw();
	EndFrame();
}

void EditorUI::SetTexture(uint64_t texture_id) {
    m_texture_id = texture_id;
}

void EditorUI::SetDarkThemeColors() {
    auto& colors = ImGui::GetStyle().Colors;

    // Headers
    colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
    colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
    colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
}

} // namespace RendererDemo
