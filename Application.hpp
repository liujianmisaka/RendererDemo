#pragma once

#include "Window.hpp"

namespace RendererDemo {

class Application {
public:
    Application();
    ~Application();

    void run();

private:
    RendererDemo::Window m_MainWindow {};
};

}