#include "Application.hpp"

#include "Log.hpp"
#include <GLFW/glfw3.h>

namespace RendererDemo {

Application::Application() {
    // init Render
    LOGGER_CORE_INFO("App Created!");
}

Application::~Application() {
    
}

void Application::run() {
    m_MainWindow.run();
}
}