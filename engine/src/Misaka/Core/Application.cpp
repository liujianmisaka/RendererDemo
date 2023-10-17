#include "Misaka/Core/Application.hpp"

#include "platform/OpenGL/OpenGLRendererAPI.hpp"


namespace RendererDemo {

Application::Application() {
    Application::Init();
}

Application::~Application() {
    Application::Close();
    delete m_Renderer;
}

void Application::Init() {
    m_MainWindow.init();
    m_Renderer = new OpenGLRendererAPI();
    m_Renderer->init();
    m_Renderer->drawExample();
}

void Application::Close() {
    m_Renderer->close();
    m_MainWindow.close();
}

void Application::Run() {
    while (!m_MainWindow.shouldClose()) {
        // m_Renderer->update();
        // m_MainWindow.update();
		m_MainScene.Update();
		m_MainScene.Render();
    }
}
} // namespace RendererDemo
