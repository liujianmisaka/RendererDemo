#include "Editor/UI/EditorUI.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Editor/UI/Utils.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"
#include "Runtime/Function/Renderer/RHI/RHI.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"

namespace RendererDemo {

void EditorUI::Initialize(EditorUIInitInfo init_info) {
    m_window_system = init_info.window_system;
    m_renderer_system = init_info.renderer_system;
    m_game_world_manager = init_info.game_world_manager;

    m_scene_hierarchy_panel.SetContext(m_game_world_manager->GetCurrentActivateScene());

    UIInit();
}

void EditorUI::Clear() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditorUI::Tick() {
    Update();
    BeginFrame();
    ImGuiRender();
    EndFrame();
    m_renderer_system->SetViewport(m_viewport_size.x, m_viewport_size.y);
    m_camera.SetAspectRatio(m_viewport_size.x / m_viewport_size.y);
    m_game_world_manager->GetCurrentActivateScene()->SetRenderCamera(m_camera);
}

void EditorUI::UIInit() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    SetDarkThemeColors();
    SetFont();

    // Init imgui docking
    GLFWwindow* window = m_window_system->GetNativeWindow();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    // TODO: use editor context to get texture id
    m_texture_id = m_renderer_system->GetImTextureID();

    m_scene_hierarchy_panel.SetContext(m_game_world_manager->GetCurrentActivateScene());
}

void EditorUI::Update() {
    m_scene_hierarchy_panel.SetContext(m_game_world_manager->GetCurrentActivateScene());
    SetCamera(m_game_world_manager->GetCurrentActivateScene()->GetRenderCamera());
}

void EditorUI::BeginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void EditorUI::ImGuiRender() {
    static bool p_open = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    } else {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen) ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    RenderMenuBar();
    RenderSettings();
    RenderViewport();
    m_scene_hierarchy_panel.OnImGuiRender();
    m_asset_panel.OnImGuiRender();
    m_log_panel.OnImGuiRender();

    ImGui::End();
}

void EditorUI::EndFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorUI::RenderMenuBar() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            // ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
            if (ImGui::MenuItem("New", "Ctrl+N")) std::cout << "New\n";

            if (ImGui::MenuItem("Open...", "Ctrl+O")) std::cout << "Open\n";

            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) std::cout << "Save As\n";

            if (ImGui::MenuItem("Exit")) std::cout << "Exit\n";
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

void EditorUI::RenderSettings() {
    ImGui::Begin("editor setting");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::Separator();
    auto position = m_camera.GetPosition();
    DrawVec3Control("Position", position);
    m_camera.SetPosition(position);

    auto rotation = m_camera.GetRotation();
    DrawVec3Control("Rotation", rotation, glm::vec3(0.0f, -90.0f, 0.0f));
    m_camera.SetRotation(rotation);

    auto aspect_ratio = m_camera.GetAspectRatio();
    if (ImGui::DragFloat("Aspect Ratio", &aspect_ratio)) {
        m_camera.SetAspectRatio(aspect_ratio);
    }

    auto fov = m_camera.GetFov();
    if (ImGui::DragFloat("Perspective FOV", &fov)) {
        m_camera.SetFov(fov);
    }
    auto near = m_camera.GetNearClip();
    if (ImGui::DragFloat("Perspective Near", &near)) {
        m_camera.SetNearClip(near);
    }
    auto far = m_camera.GetFarClip();
    if (ImGui::DragFloat("Perspective Far", &far)) {
        m_camera.SetFarClip(far);
    }

    // auto view_matrix = camera.GetViewMatrix();
    // ImGui::Text("View Matrix");
    // ImGui::Text("%f %f %f %f", view_matrix[0][0], view_matrix[0][1], view_matrix[0][2], view_matrix[0][3]);
    // ImGui::Text("%f %f %f %f", view_matrix[1][0], view_matrix[1][1], view_matrix[1][2], view_matrix[1][3]);
    // ImGui::Text("%f %f %f %f", view_matrix[2][0], view_matrix[2][1], view_matrix[2][2], view_matrix[2][3]);
    // ImGui::Text("%f %f %f %f", view_matrix[3][0], view_matrix[3][1], view_matrix[3][2], view_matrix[3][3]);

    // auto projection_matrix = camera.GetPerspectiveProjectionMatrix();
    // ImGui::Text("Projection Matrix");
    // ImGui::Text("%f %f %f %f", projection_matrix[0][0], projection_matrix[0][1], projection_matrix[0][2],
    //             projection_matrix[0][3]);
    // ImGui::Text("%f %f %f %f", projection_matrix[1][0], projection_matrix[1][1], projection_matrix[1][2],
    //             projection_matrix[1][3]);
    // ImGui::Text("%f %f %f %f", projection_matrix[2][0], projection_matrix[2][1], projection_matrix[2][2],
    //             projection_matrix[2][3]);
    // ImGui::Text("%f %f %f %f", projection_matrix[3][0], projection_matrix[3][1], projection_matrix[3][2],
    //             projection_matrix[3][3]);

    ImGui::End();
}

void EditorUI::RenderViewport() {
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImVec2 availableSize = ImGui::GetContentRegionAvail();
    m_viewport_size = availableSize;
    ImGui::Image(m_texture_id, availableSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
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

void EditorUI::SetFont() {
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("Asset/fonts/opensans/OpenSans-Bold.ttf", 25.0f);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("Asset/fonts/opensans/OpenSans-Regular.ttf", 25.0f);
}

} // namespace RendererDemo
