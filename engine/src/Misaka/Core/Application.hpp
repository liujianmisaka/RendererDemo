#pragma once

#include "Misaka/Core/Window.hpp"
#include "Misaka/Renderer/Renderer.hpp"

namespace RendererDemo {

class Application {
public:
    Application();
    ~Application();

    void run();

private:
    void init();
    void close();

private:
    RendererDemo::Window m_MainWindow;
    RendererDemo::Renderer* m_Renderer;
};

} // namespace RendererDemo