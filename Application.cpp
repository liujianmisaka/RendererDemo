#include "Application.hpp"

#include "Log.hpp"

namespace RendererDemo {

Application::Application(ApplicationInfo appInfo) 
    : m_AppInfo(appInfo)
{
    LOGGER_CORE_INFO("App Create!");
    // init window
    // init Render
}

void Application::run() {
    while(true){
        
    }
}
}