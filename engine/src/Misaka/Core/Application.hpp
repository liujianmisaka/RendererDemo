#pragma once

#include <string>
#include <vector>
#include "Misaka/Core/Window.hpp"
#include "Misaka/Core/Renderer.hpp"
#include "Misaka/Core/Scene.hpp"

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

	std::vector<RendererDemo::Scene> m_Scenes;
	RendererDemo::Scene m_MainScene;
};

Application* CreateApplicationInstace();

} // namespace RendererDemo
