#include "Misaka/Application.hpp"

#include "Misaka/Log.hpp"
#include "platform/OpenGLRendererAPI.hpp"


namespace RendererDemo {

Application::Application() {
    // init Render
    LOGGER_CORE_INFO("App Created!");
}

Application::~Application() {
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
    LOGGER_CORE_INFO("1");
    while (!m_MainWindow.shouldClose()) {
        LOGGER_CORE_INFO("2");
        m_Renderer->update();
        LOGGER_CORE_INFO("3");
        m_MainWindow.update();
    }
    LOGGER_CORE_INFO("4");
}
} // namespace RendererDemo