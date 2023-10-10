#pragma once

#include <string>

#include "Window.hpp"

namespace RendererDemo {

struct ApplicationInfo {
    std::string name = "RendererDemo Application";
};

class Application {
public:
    Application(RendererDemo::ApplicationInfo appInfo);
    ~Application() {};

    void run();

    void close();

private:
    RendererDemo::ApplicationInfo m_AppInfo;
    RendererDemo::Window m_MainWindow;

    bool m_IsRunning = true;
};

}