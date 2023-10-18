#pragma once

#include <string>
#include "Misaka/Core/IWindow.hpp"
#include "Misaka/Core/IWorld.hpp"
#include "Misaka/Core/IRenderer.hpp"

namespace RendererDemo {

class Application {
public:
    Application() = default;
    virtual ~Application() = default;

    virtual void Initialize();
    virtual void Destroy();

    void Run();

    virtual const std::string& GetClassName() { return m_ClassName; }

private:
    std::string m_ClassName = "Application";

    RendererDemo::IWindow* m_Window;
    RendererDemo::IWorld* m_MainWorld;
    RendererDemo::IRenderer* m_Renderer;

	float m_LastTime = 0;
};

Application* CreateApplicationInstace();

} // namespace RendererDemo
