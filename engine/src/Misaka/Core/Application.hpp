#pragma once

#include <string>
#include "Misaka/Core/Window.hpp"
#include "Misaka/Core/Scene.hpp"
#include "Misaka/Core/Renderer.hpp"

namespace RendererDemo {

class Application {
public:
    Application();
    virtual ~Application();

    void Run();

    virtual const std::string GetClassName() { return m_ClassName; }
private:
	void Init();
	void Close();

private:
    std::string m_ClassName = "Application";

    RendererDemo::Window* m_Window;
	RendererDemo::Scene* m_MainScene;
	RendererDemo::Renderer* m_Renderer;
};

Application* CreateApplicationInstace();

} // namespace RendererDemo
