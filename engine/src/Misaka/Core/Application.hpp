#pragma once

#include <string>
#include "Misaka/Core/Window.hpp"
#include "Misaka/Renderer/Renderer.hpp"

namespace RendererDemo {

class Application {
public:
    Application();
    virtual ~Application();

    void Run();

    //
    virtual std::string GetAppName() { return m_AppName; }

private:
    void Init();
    void Close();

private:
    RendererDemo::Window m_MainWindow;
    RendererDemo::Renderer* m_Renderer;

    std::string m_AppName = "Application";
};

Application* CreateApplicationInstace();

} // namespace RendererDemo
