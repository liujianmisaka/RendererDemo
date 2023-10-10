#include "Application.hpp"

#include "Log.hpp"

namespace RendererDemo {

Application::Application(ApplicationInfo appInfo) 
    : m_AppInfo(appInfo)
{
    m_MainWindow = RendererDemo::Window{};
    // init Render
    LOGGER_CORE_INFO("App Create!");
}

void Application::run() {
    while(m_IsRunning) {
        m_MainWindow.run();
    }
}
}