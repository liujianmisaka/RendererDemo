#include "Misaka/Core/Application.hpp"

#include "platform/OpenGL/OpenGLRendererAPI.hpp"


namespace RendererDemo {

Application::Application() {
    Application::init();
}

Application::~Application() {
    Application::close();
    delete m_Renderer;
}

void Application::init() {
    m_MainWindow.init();
    m_Renderer = new OpenGLRendererAPI;
    m_Renderer->init();
    m_Renderer->drawExample();
}

void Application::close() {
    m_Renderer->close();
    m_MainWindow.close();
}

void Application::run() {
    while (!m_MainWindow.shouldClose()) {
        m_Renderer->update();
        m_MainWindow.update();
    }
}
} // namespace RendererDemo