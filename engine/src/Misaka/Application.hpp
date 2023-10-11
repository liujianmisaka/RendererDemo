#pragma once

#include "Misaka/Renderer.hpp"
#include "Misaka/Window.hpp"


namespace RendererDemo {

class Application {
public:
    Application();
    ~Application();

    void init();

    void close();

    void run();

private:
    RendererDemo::Window m_MainWindow;
    RendererDemo::Renderer* m_Renderer;
};

}