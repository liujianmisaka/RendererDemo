#include "Misaka/Core/Application.hpp"

// #include "platform/OpenGL/OpenGLRendererAPI.hpp"


namespace RendererDemo {

Application::Application() {
    
}

Application::~Application() {
    
}


void Application::Run() {
    while (!m_Window->ShouldClose()) {
		m_Window->Update();    // Event
		m_MainScene->Update();
		m_Renderer->Render(m_MainScene);
    }
}
} // namespace RendererDemo
