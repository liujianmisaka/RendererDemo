#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLRHI.hpp"
#include <iostream>
#include "Runtime/Function/Renderer/System/WindowSystem.hpp"


namespace RendererDemo {

void OpenGLRHI::Initialize(RHIInitInfo rhi_init_info) {

	m_window = rhi_init_info.window_system->GetNativeWindow();

    // 初始化 glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize glad" << std::endl;
    }
}

} // namespace RendererDemo
